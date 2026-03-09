# test/Makefile
#
# Build CP/M test programs for libcpm3-z80.
#
# Each test source is compiled and linked against the built library into
# an Intel-HEX file (.ihx) then converted to a CP/M .COM binary via
# sdobjcopy (outputs binary starting at the first IHX record address, 0x0100).
#
# Intermediate files (.ihx) are kept in BUILD_DIR (./build/).
# Final .COM files are written directly to OUT_DIR ($(BIN_DIR), i.e. bin/).
#
# Targets:
#   all          Build all test .com files into bin/
#   docker       Build library + tests inside Docker (wischner/sdcc-z80)
#   clean        Remove test build artefacts and .com files from bin/
#
# Copy the .com files from bin/ to a CP/M disk and run them on the
# target machine (or a CP/M emulator such as z80pack, YAZE, etc.).
# Expected output per test:
#   PASS <test_name>              -- individual test passed
#   FAIL <test_name> (N)          -- individual test failed
#   PASS all N tests              -- all tests in the binary passed
#   FAIL N failures in F/T tests  -- some tests failed
#
# We only allow compilation on Linux (same restriction as the project root).
ifneq ($(shell uname), Linux)
ifndef INSIDE_DOCKER
$(error OS must be Linux!)
endif
endif

ROOT            = $(realpath ..)
BIN_DIR         = $(ROOT)/bin
INC_DIR         = $(ROOT)/include
BUILD_DIR       = ./build
OUT_DIR         = $(BIN_DIR)

DOCKER_IMAGE    = wischner/sdcc-z80
DOCKER_RUN      = docker run --rm \
                  -v "$(ROOT)":/src \
                  -w /src \
                  -e INSIDE_DOCKER=1 \
                  --user $(shell id -u):$(shell id -g) \
                  $(DOCKER_IMAGE)

CC      = sdcc
CFLAGS  = -mz80 --std-c11 \
          -I$(INC_DIR) --nostdinc --nostdlib
LDFLAGS = -mz80 --std-c11 \
          --no-std-crt0 --nostdinc --nostdlib \
          --code-loc 0x100 --data-loc 0

CRT0    = $(BIN_DIR)/crt0cpm3-z80.rel
LIB     = $(BIN_DIR)/libcpm3-z80.lib

# SDCC runtime helpers (integer/float stubs). Inherited from root make or
# downloaded here if test/Makefile is invoked directly.
LIBSDCC_VER ?= 0.0.1
LIBSDCC_URL ?= https://github.com/retro-vault/libsdcc-z80/releases/download/v$(LIBSDCC_VER)/libsdcc-z80-$(LIBSDCC_VER).tar.gz
SDCCLIB     ?= $(ROOT)/lib/libsdcc-z80.lib

# One binary per test module (8.3 names for comfort on CP/M).
TESTS   = tctype tstring tstdlib tstdio ttime tmath tmem tfile tsdcc tsetjmp
BINS    = $(addprefix $(OUT_DIR)/, $(addsuffix .com, $(TESTS)))

.PHONY: all
all: $(BUILD_DIR) $(BINS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Build the library and CRT0 if not present. Invokes the root Makefile.
# This is a file rule (not phony) so it only fires when the files are absent.
$(LIB) $(CRT0):
	$(MAKE) -C $(ROOT) all

# Download SDCC runtime helpers if not present (idempotent).
$(SDCCLIB):
	mkdir -p $(ROOT)/lib
	curl -sL $(LIBSDCC_URL) | \
	  tar -xzf - --strip-components=2 -C $(ROOT)/lib \
	  libsdcc-z80-$(LIBSDCC_VER)/lib/libsdcc-z80.lib

# Rule: .c -> .rel (compile) -> .ihx (link) -> .com (sdobjcopy)
#
# sdobjcopy -I ihex -O binary emits a flat binary starting at the first
# record address in the IHX file (0x0100 for CP/M), so the output is a
# valid .COM file with no leading zero-padding.
#
# Link order: CRT0, application, libcpm3-z80, libsdcc-z80.
# libsdcc-z80 must come last -- it resolves the low-level arithmetic and
# float stubs that libcpm3-z80 math functions call into.
$(OUT_DIR)/%.com: %.c $(CRT0) $(LIB) $(SDCCLIB) | $(OUT_DIR)
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$*.rel $<
	$(CC) $(LDFLAGS) -o $(BUILD_DIR)/$*.ihx $(CRT0) $(BUILD_DIR)/$*.rel $(LIB) $(SDCCLIB)
	sdobjcopy -I ihex -O binary $(BUILD_DIR)/$*.ihx $@

.PHONY: docker
docker:
	$(DOCKER_RUN) make all

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(BINS)
