# Virtual paths are all subfolders!
DIRS	=	$(wildcard */)
vpath %.c $(DIRS)
vpath %.s $(DIRS)
vpath %.h $(DIRS)

# Source files.
C_SRCS	=	$(wildcard *.c) $(wildcard */*.c)
S_SRCS	=	$(wildcard *.s) $(wildcard */*.s)
OBJS	=	$(addprefix $(BUILD_DIR)/, \
				$(notdir \
					$(patsubst %.c,%.rel,$(C_SRCS)) \
					$(patsubst %.s,%.rel,$(S_SRCS)) \
				) \
			)
TARGET = libcpm3-z80

# Rules.
.PHONY: all
all:	$(BUILD_DIR)/$(TARGET).lib

$(BUILD_DIR)/$(TARGET).lib: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.rel:	%.s
	$(AS) $(ASFLAGS) $(BUILD_DIR)/$(@F) $<

$(BUILD_DIR)/%.rel: %.c
	$(CC) -c -o $(BUILD_DIR)/$(@F) $< $(CFLAGS)

$(BUILD_DIR)/%.rel: %.h