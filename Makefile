# We only allow compilation on Linux!
ifneq ($(shell uname), Linux)
$(error OS must be Linux!)
endif

# --------------------------------------------------------------------------
# Folders
# --------------------------------------------------------------------------
export ROOT         = $(realpath .)
export BUILD_DIR   ?= $(ROOT)/build
export BIN_DIR     ?= $(ROOT)/bin
export INC_DIR      = $(ROOT)/include

# --------------------------------------------------------------------------
# Library and CRT0 names
# --------------------------------------------------------------------------
export TARGET       = libcpm3-z80
export CRT0         = crt0cpm3-z80
export CRT0EXT      = .rel

# --------------------------------------------------------------------------
# Platform selector. The built-in default platform is "none".
# Any other platform omits the default helpers -- link your own
# implementations.
# --------------------------------------------------------------------------
PLATFORM            ?= none
PLATFORM_UPPER      := $(shell echo '$(PLATFORM)' | tr 'a-z-' 'A-Z_')
export PLATFORM

# --------------------------------------------------------------------------
# Tools and flags
# --------------------------------------------------------------------------
export CC           = sdcc
export CFLAGS       = -mz80 --std-c11 -I. -I$(INC_DIR) --nostdinc --nostdlib --debug \
                      -DPLATFORM_$(PLATFORM_UPPER) \
                      -DPLATFORM_NAME=$(PLATFORM)
export LDFLAGS      = -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib --debug \
                      --code-loc 0x100 --data-loc 0
export AS           = sdasz80
export ASFLAGS      = -xlos -g
export AR           = sdar
export ARFLAGS      = -rc
export CPP          = sdcpp
export LD           = sdldz80

# --------------------------------------------------------------------------
# SDCC runtime helpers (needed only when linking test executables).
# Downloaded automatically by 'make test' if not present.
# --------------------------------------------------------------------------
LIBSDCC_VER         = 1.0.1
LIBSDCC_URL         = https://github.com/retro-vault/libsdcc-z80/releases/download/v$(LIBSDCC_VER)/libsdcc-z80-$(LIBSDCC_VER).tar.gz
export LIBSDCC      = $(ROOT)/lib/libsdcc-z80.lib

# --------------------------------------------------------------------------
# Docker (on by default). Set DOCKER=off for a native build.
# --------------------------------------------------------------------------
DOCKER              ?= on

DOCKER_IMAGE        = wischner/sdcc-z80
DOCKER_RUN          = docker run --rm \
                      -v "$(ROOT)":/src \
                      -w /src \
                      -e INSIDE_DOCKER=1 \
                      -e PLATFORM=$(PLATFORM) \
                      --user $(shell id -u):$(shell id -g) \
                      $(DOCKER_IMAGE)

DOCKER_TEST_IMAGE   = libcpm3-z80-test
DOCKER_TEST_RUN     = docker run --rm \
                      -v "$(ROOT)":/src \
                      $(DOCKER_TEST_IMAGE)

# --------------------------------------------------------------------------
# Native tool check (only when building without Docker)
# --------------------------------------------------------------------------
ifndef INSIDE_DOCKER
ifeq ($(DOCKER),off)
REQUIRED = $(CC) $(AR) $(AS) $(CPP) $(LD)
K := $(foreach exec,$(REQUIRED),\
    $(if $(shell which $(exec)),,$(error "$(exec) not found. Install SDCC or use DOCKER=on.")))
endif
endif

# --------------------------------------------------------------------------
# Internal native build (called directly or from inside Docker)
# --------------------------------------------------------------------------
SUBDIRS = src

.PHONY: _build
_build: $(BUILD_DIR) $(SUBDIRS)
	cp --dereference $(BUILD_DIR)/$(TARGET).lib $(BIN_DIR)
	cp --dereference $(BUILD_DIR)/$(CRT0).rel   $(BIN_DIR)/$(CRT0)$(CRT0EXT)
	cp -R --dereference $(ROOT)/include          $(BIN_DIR)

.PHONY: $(BUILD_DIR)
$(BUILD_DIR):
	rm -rf  $(BUILD_DIR) $(BIN_DIR)
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ \
		AS="$(AS)" CC="$(CC)" AR="$(AR)" CPP="$(CPP)" LD="$(LD)" \
		CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"

# --------------------------------------------------------------------------
# make          Build the library
# --------------------------------------------------------------------------
.DEFAULT_GOAL := all

ifeq ($(DOCKER),on)
.PHONY: all
all:
	$(DOCKER_RUN) make _build
else
.PHONY: all
all: _build
endif

# --------------------------------------------------------------------------
# make test     Build library + tests, run in CP/M emulator (Docker only)
# --------------------------------------------------------------------------
ifeq ($(DOCKER),on)
.PHONY: test
test: $(LIBSDCC)
	docker build -t $(DOCKER_TEST_IMAGE) -f test/Dockerfile.cpm test/
	$(DOCKER_RUN) sh -c "make _build && make -C test SDCCLIB='/src/lib/libsdcc-z80.lib'"
	$(DOCKER_TEST_RUN) /src/test/run_tests.sh tctype tstring tstdlib tstdio ttime tmath tmem tfile tsdcc tsetjmp textraa textrab

$(LIBSDCC):
	mkdir -p $(ROOT)/lib
	curl -sL $(LIBSDCC_URL) | \
	  tar -xzf - --strip-components=2 -C $(ROOT)/lib \
	  libsdcc-z80-$(LIBSDCC_VER)/lib/libsdcc-z80.lib
else
.PHONY: test
test:
	$(error 'make test' requires Docker. Remove DOCKER=off to enable.)
endif

# --------------------------------------------------------------------------
# make clean    Remove build artifacts
# --------------------------------------------------------------------------
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(ROOT)/lib

# --------------------------------------------------------------------------
# make help
# --------------------------------------------------------------------------
.PHONY: help
help:
	@echo "Usage: make [target] [VARIABLE=value ...]"
	@echo ""
	@echo "Targets:"
	@echo "  (default)    Build the library"
	@echo "  test         Build library + tests and run in CP/M emulator (Docker only)"
	@echo "  clean        Remove build/ and bin/"
	@echo ""
	@echo "Variables:"
	@echo "  DOCKER=on           Build inside Docker (default)"
	@echo "  DOCKER=off          Build natively (requires SDCC on PATH; 'make test' unavailable)"
	@echo "  PLATFORM=<name>     Platform selector (default: none)"
	@echo "                      Defines PLATFORM_<NAME>. Non-default omits _msleep()/_libinit()."
	@echo "  BUILD_DIR=<path>    Override intermediate build directory (default: build/)"
	@echo "  BIN_DIR=<path>      Override output directory (default: bin/)"
