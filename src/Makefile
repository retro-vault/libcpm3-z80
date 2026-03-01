# Virtual paths are all subfolders!
DIRS    = $(wildcard */)
vpath %.c $(DIRS)
vpath %.s $(DIRS)
vpath %.h $(DIRS)

# Source files.
C_SRCS  = $(wildcard *.c) $(wildcard */*.c)
S_SRCS  = $(filter-out $(CRT0).s, $(wildcard *.s) $(wildcard */*.s))
HDRS    = $(wildcard *.h) $(wildcard */*.h)
OBJS    = $(addprefix $(BUILD_DIR)/, \
              $(notdir \
                  $(patsubst %.c,%.rel,$(C_SRCS)) \
                  $(patsubst %.s,%.rel,$(S_SRCS)) \
              ) \
          )

# Rules.
.PHONY: all
all: $(BUILD_DIR)/$(TARGET).lib $(BUILD_DIR)/$(CRT0).rel

$(BUILD_DIR)/$(TARGET).lib: $(OBJS) $(HDRS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(BUILD_DIR)/$(CRT0).rel: $(CRT0).s
	$(AS) $(ASFLAGS) $(BUILD_DIR)/$(@F) $<

$(BUILD_DIR)/%.rel: %.s
	$(AS) $(ASFLAGS) $(BUILD_DIR)/$(@F) $<

$(BUILD_DIR)/%.rel: %.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$*.rel $<
