# We only allow compilation on linux!
ifneq ($(shell uname), Linux)
$(error OS must be Linux!)
endif

# Check if all required tools are on the system.
REQUIRED = sdcc sdar sdasz80
K := $(foreach exec,$(REQUIRED),\
    $(if $(shell which $(exec)),,$(error "$(exec) not found. Please install or add to path.")))

# Default platform is no platform.
export PLATFORM 	=	

# Global settings: folders.
export ROOT			=	$(realpath .)
export BUILD_DIR	=	$(ROOT)/build
export BIN_DIR		=	$(ROOT)/bin
export INC_DIR		=	$(ROOT)/include

# Build reduced version of libraries?
export SLIM			=

# Globa settings: tools.
export CC			=	sdcc
export CFLAGS		=	--std-c11 -mz80 -I. -I$(INC_DIR) --no-std-crt0 --nostdinc --nostdlib --debug -D PLATFORM=$(PLATFORM) -D SLIM=$(SLIM)
export AS			=	sdasz80
export ASFLAGS		=	-xlos -g
export AR			=	sdar
export ARFLAGS		=	-rc

# crt0.s
export CRT0			=	crt0cpm3-z80

# Subfolders for make.
SUBDIRS 			=	src
SUBMODULES 			= 	lib/libsdcc-z80

# Rules.
.PHONY: all
all:	$(BUILD_DIR) $(SUBMODULES) $(SUBDIRS)
	cp $(BUILD_DIR)/*.lib $(BIN_DIR)
	cp $(BUILD_DIR)/$(CRT0).rel $(BIN_DIR)

.PHONY: $(BUILD_DIR)
$(BUILD_DIR):
	# Create build dir.
	mkdir -p $(BUILD_DIR)
	# Remove bin dir (we are going to write again).
	rm -f -r $(BIN_DIR)
	# And re-create!
	mkdir -p $(BIN_DIR)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: $(SUBMODULES)
$(SUBMODULES):
	# Pass current build and bin directories.
	$(MAKE) -C $@ BUILD_DIR=$(BUILD_DIR) BIN_DIR=$(BIN_DIR)
	
.PHONY: clean
clean:
	rm -f -r $(BUILD_DIR)