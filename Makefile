# We only allow compilation on linux!
ifneq ($(shell uname), Linux)
$(error OS must be Linux!)
endif

# Default platform is no platform.
export PLATFORM 	=

# Global settings: folders.
export ROOT			=	$(realpath .)

# PREFIX is a standardized env variable for the target install directory.
export PREFIX		=	$(ROOT)/bin

export BUILD_DIR	=	$(ROOT)/build
export BIN_DIR		=	$(PREFIX)
export INC_DIR		=	$(ROOT)/include

# Build reduced version of libraries?
export SLIM			=

# Instruction set. Could be -mz180 as well, for example.
export ISET			= -mz80

# Global settings: tools.
export CC			=	sdcc
export CFLAGS		=	--std-c11 $(ISET) -I. -I$(INC_DIR) --no-std-crt0 --nostdinc --nostdlib --debug -D PLATFORM=$(PLATFORM) -D SLIM=$(SLIM)
export AS			=	sdasz80
export ASFLAGS		=	-xlos -g
export AR			=	sdar
export ARFLAGS		=	-rc
export CPP			=	sdcpp
export LD			=	sdldz80

# Check if all required tools are on the system.
REQUIRED = ${CC} ${AR} ${AS} ${CPP} ${LD}
K := $(foreach exec,$(REQUIRED),\
    $(if $(shell which $(exec)),,$(error "$(exec) not found. Please install or add to path.")))

# crt0.s
export CRT0			=	crt0cpm3-z80
export CRT0EXT			=	.rel

# Subfolders for make.
SUBDIRS 			=	src
SUBMODULES 			= 	lib/libsdcc-z80

# Rules.
.PHONY: all
all:	$(BUILD_DIR) $(SUBMODULES) $(SUBDIRS)
	cp --dereference $(BUILD_DIR)/*.lib $(BIN_DIR)
	cp --dereference $(BUILD_DIR)/$(CRT0).rel $(BIN_DIR)/$(CRT0)$(CRT0EXT)
	cp -R --dereference $(ROOT)/include $(BIN_DIR)

# "make install" is somewhat expected to be present.
.PHONY: install
install: all

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
	$(MAKE) -C $@ \
		AS="$(AS)" \
		CC="$(CC)" \
		AR="$(AR)" \
		CPP="$(CPP)" \
		LD="$(LD)" \
		REQUIRED="$(AS) $(CC) $(AR) $(CPP) $(LD)" \
		CFLAGS="$(CFLAGS)"

.PHONY: $(SUBMODULES)
$(SUBMODULES):
	# Pass current settings to the submodules.
	$(MAKE) -C $@ \
		BUILD_DIR=$(BUILD_DIR) \
		BIN_DIR=$(BIN_DIR) \
		AS="$(AS)" \
		CC="$(CC)" \
		AR="$(AR)" \
		CPP="$(CPP)" \
		LD="$(LD)" \
		REQUIRED="$(AS) $(CC) $(AR) $(CPP) $(LD)" \
		CFLAGS="$(CFLAGS)"


.PHONY: clean
clean:
	rm -f -r $(BUILD_DIR)

