# We only allow compilation on linux!
ifneq ($(shell uname), Linux)
$(error OS must be Linux!)
endif

# Global settings: folders.
export ROOT         = $(realpath .)

# PREFIX is a standardized env variable for the target install directory.
export PREFIX       = $(ROOT)/bin

export BUILD_DIR    = $(ROOT)/build
export BIN_DIR      = $(PREFIX)
export INC_DIR      = $(ROOT)/include

# Library and CRT0 names.
export TARGET       = libcpm3-z80
export CRT0         = crt0cpm3-z80
export CRT0EXT      = .rel

# Global settings: tools.
export CC           = sdcc
export CFLAGS       = -mz80 --std-c11 -I. -I$(INC_DIR) --nostdinc --nostdlib --debug
export LDFLAGS      = -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib --debug \
                      --code-loc 0x100 --data-loc 0
export AS           = sdasz80
export ASFLAGS      = -xlos -g
export AR           = sdar
export ARFLAGS      = -rc
export CPP          = sdcpp
export LD           = sdldz80

# SDCC runtime helpers (integer/float assembly stubs).
# Only needed when linking final executables; not required to build the library.
LIBSDCC_VER         = 1.0.1
LIBSDCC_URL         = https://github.com/retro-vault/libsdcc-z80/releases/download/v$(LIBSDCC_VER)/libsdcc-z80-$(LIBSDCC_VER).tar.gz
export LIBSDCC      = $(ROOT)/lib/libsdcc-z80.lib

# Docker build support.
DOCKER_IMAGE        = wischner/sdcc-z80
DOCKER_RUN          = docker run --rm \
                      -v "$(ROOT)":/src \
                      -w /src \
                      -e INSIDE_DOCKER=1 \
                      --user $(shell id -u):$(shell id -g) \
                      $(DOCKER_IMAGE)

# Root-privileged docker run used only by docker-clean to handle build
# artifacts that were created by a previous root Docker container.
DOCKER_RUN_ROOT     = docker run --rm \
                      -v "$(ROOT)":/src \
                      -w /src \
                      $(DOCKER_IMAGE)

# CP/M emulator (RunCPM) Docker image for running test .COM binaries.
DOCKER_TEST_IMAGE   = libcpm3-z80-test
DOCKER_TEST_RUN     = docker run --rm \
                      -v "$(ROOT)":/src \
                      $(DOCKER_TEST_IMAGE)

# Default goal is 'docker' so bare 'make' builds the library inside Docker
# without requiring SDCC installed locally.
# Use 'make native' only when building natively (requires SDCC on PATH).
# Use 'make test' to build the library + tests and run them in the CP/M emulator.
.DEFAULT_GOAL := docker

# Check that SDCC tools are present -- only when explicitly building natively.
ifndef INSIDE_DOCKER
ifneq (,$(filter native install,$(MAKECMDGOALS)))
REQUIRED = $(CC) $(AR) $(AS) $(CPP) $(LD)
K := $(foreach exec,$(REQUIRED),\
    $(if $(shell which $(exec)),,$(error "$(exec) not found. Please install or add to path.")))
endif
endif

# Subfolders for make.
SUBDIRS             = src

# Rules.
.PHONY: lib
lib: $(BUILD_DIR) $(SUBDIRS)
	cp --dereference $(BUILD_DIR)/$(TARGET).lib $(BIN_DIR)
	cp --dereference $(BUILD_DIR)/$(CRT0).rel $(BIN_DIR)/$(CRT0)$(CRT0EXT)
	cp -R --dereference $(ROOT)/include $(BIN_DIR)

# 'all' is an alias for 'lib' (used internally by sub-makes).
.PHONY: all
all: lib

# Build library only, natively (requires SDCC on PATH). No tests.
.PHONY: native
native: lib

.PHONY: install
install: lib
	install -d $(DESTDIR)$(PREFIX)/lib $(DESTDIR)$(PREFIX)/include
	cp $(BIN_DIR)/$(TARGET).lib $(DESTDIR)$(PREFIX)/lib/
	cp $(BIN_DIR)/$(CRT0)$(CRT0EXT) $(DESTDIR)$(PREFIX)/lib/
	cp -R $(INC_DIR)/. $(DESTDIR)$(PREFIX)/include/

# Default: build library only inside Docker.
.PHONY: docker
docker:
	$(DOCKER_RUN) make lib

# Build library + tests inside Docker, then run tests in the CP/M emulator.
.PHONY: test
test: docker-test-build
	$(DOCKER_RUN) sh -c "make lib && make -C test SDCCLIB='$(LIBSDCC)'"
	$(DOCKER_TEST_RUN) /src/test/run_tests.sh tctype tstring tstdlib tstdio ttime tmath tmem tfile tsdcc tsetjmp

.PHONY: docker-clean
docker-clean:
	$(DOCKER_RUN_ROOT) sh -c "rm -rf /src/build /src/bin"

# Build the CP/M test-runner Docker image (once; rebuild with docker-test-rebuild).
.PHONY: docker-test-build
docker-test-build:
	docker build -t $(DOCKER_TEST_IMAGE) -f test/Dockerfile.cpm test/

# Force-rebuild the CP/M test-runner image (no cache).
.PHONY: docker-test-rebuild
docker-test-rebuild:
	docker build --no-cache -t $(DOCKER_TEST_IMAGE) -f test/Dockerfile.cpm test/

.PHONY: $(BUILD_DIR)
$(BUILD_DIR):
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)
	rm -rf $(BIN_DIR)
	mkdir -p $(BIN_DIR)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ \
		AS="$(AS)" \
		CC="$(CC)" \
		AR="$(AR)" \
		CPP="$(CPP)" \
		LD="$(LD)" \
		CFLAGS="$(CFLAGS)" \
		LDFLAGS="$(LDFLAGS)"

# Download the SDCC runtime helpers library.
# Run once before building any final executable (e.g. test programs).
.PHONY: deps
deps: $(LIBSDCC)

$(LIBSDCC):
	mkdir -p $(ROOT)/lib
	curl -sL $(LIBSDCC_URL) | \
	  tar -xzf - --strip-components=2 -C $(ROOT)/lib \
	  libsdcc-z80-$(LIBSDCC_VER)/lib/libsdcc-z80.lib

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: help
help:
	@echo "Targets:"
	@echo "  (default)    Build library inside Docker ($(DOCKER_IMAGE))"
	@echo "  docker       Build library inside Docker ($(DOCKER_IMAGE))"
	@echo "  test         Build library + tests inside Docker, then run in CP/M emulator"
	@echo "  native       Build library natively (requires SDCC on PATH; no tests)"
	@echo "  deps         Download libsdcc-z80 runtime helpers to lib/"
	@echo "  install      Install to DESTDIR\$(PREFIX) (default: bin/)"
	@echo "  clean        Remove build artifacts"
	@echo "  docker-clean       Remove build artifacts via Docker (handles root-owned files)"
	@echo "  docker-test-build  Build CP/M emulator Docker image (RunCPM)"
	@echo "  docker-test-rebuild Rebuild CP/M emulator Docker image (no cache)"
	@echo ""
	@echo "Variables:"
	@echo "  DESTDIR=<path>   Installation prefix (for make install)"
	@echo ""
	@echo "Note: run 'make deps' once before 'make test'."
	@echo "Note: 'make test' requires the CP/M test Docker image (built automatically)."
