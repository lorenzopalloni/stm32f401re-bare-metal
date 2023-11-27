REQUIRED_TOOLS := arm-none-eabi-gcc arm-none-eabi-g++
$(foreach tool,$(REQUIRED_TOOLS),\
    $(if $(shell which $(tool)),,$(error "No $(tool) in PATH")))

# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
Q := @
endif

# Useful variables
TARGET_NAME     = firmware
OPENCM3_DIR     = ../libopencm3
INC_DIR 		= inc
SRC_DIR         = src
SHARED_INC_DIR  = ../shared/inc
SHARED_SRC_DIR  = ../shared/src
BOOTLOADER_DIR  = ../bootloader

LIBNAME			= opencm3_stm32f4
DEFS			+= -DSTM32F4
FP_FLAGS		?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS		+= -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

# Linkerscript
LDSCRIPT 		= linkerscript.ld
LDLIBS			+= -l$(LIBNAME)
LDFLAGS			+= -L$(OPENCM3_DIR)/lib

# Includes
DEFS			+= -I$(OPENCM3_DIR)/include
DEFS			+= -I$(INC_DIR)
DEFS			+= -I$(SHARED_INC_DIR)

# Source files
OBJS			+= $(SRC_DIR)/$(TARGET_NAME).o
OBJS			+= $(SRC_DIR)/bootloader.o
OBJS			+= $(SRC_DIR)/timer.o
OBJS			+= $(SHARED_SRC_DIR)/core/system.o
OBJS			+= $(SHARED_SRC_DIR)/core/uart.o
OBJS			+= $(SHARED_SRC_DIR)/core/ring-buffer.o

# Common C and C++ flags
OPT				:= -Os
DEBUG			:= -ggdb3

C_AND_CPP_FLAGS += $(OPT) $(DEBUG) $(ARCH_FLAGS) $(DEFS)
C_AND_CPP_FLAGS	+= -Wextra -Wshadow -Wall -Wundef -Wredundant-decls
C_AND_CPP_FLAGS += -fno-common -ffunction-sections -fdata-sections
C_AND_CPP_FLAGS += -MMD -MP

# C flags
CSTD			?= -std=c99
CFLAGS			+= $(CSTD) $(C_AND_CPP_FLAGS)
CFLAGS 			+= -Wimplicit-function-declaration
CFLAGS			+= -Wmissing-prototypes -Wstrict-prototypes

# C++ flags
CXXSTD			?= -std=c++14
CXXFLAGS		+= $(CXXSTD) $(C_AND_CPP_FLAGS)
CXXFLAGS		+= -Weffc++

# Linker flags
LDFLAGS			+= --static -nostartfiles -T$(LDSCRIPT) $(ARCH_FLAGS) $(DEBUG)
LDFLAGS			+= -Wl,-Map=$(*).map -Wl,--cref
LDFLAGS			+= -Wl,--gc-sections
ifeq ($(V),99)
LDFLAGS			+= -Wl,--print-gc-sections
endif

# Used libraries
LDLIBS			+= -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

# GCC config
PREFIX			?= arm-none-eabi-

CC				:= $(PREFIX)gcc
CXX				:= $(PREFIX)g++
LD				:= $(PREFIX)gcc
AR				:= $(PREFIX)ar
AS				:= $(PREFIX)as
OBJCOPY			:= $(PREFIX)objcopy
OBJDUMP			:= $(PREFIX)objdump
GDB				:= $(PREFIX)gdb
SIZE			:= $(PREFIX)size

all: $(TARGET_NAME).elf $(TARGET_NAME).bin

images: $(TARGET_NAME).images

# Helper macro (e.g. "make print-OPENCM3_DIR") to see how it is resolved
print-%:
	@echo $*=$($*)

%.images: %.bin %.hex %.srec %.list %.map
	@printf "*** $* images generated ***\n"

%.bin: %.elf
	@printf "  OBJCOPY $@\n"
	$(Q)$(OBJCOPY) -Obinary $< $@

%.hex: %.elf
	@printf "  OBJCOPY $@\n"
	$(Q)$(OBJCOPY) -Oihex $< $@

%.srec: %.elf
	@printf "  OBJCOPY $@\n"
	$(Q)$(OBJCOPY) -Osrec $< $@

%.list: %.elf
	@printf "  OBJDUMP $@\n"
	$(Q)$(OBJDUMP) -S $< > $@

$(OPENCM3_DIR)/lib/lib$(LIBNAME).a:
	$(warning $(LIBNAME).a not found, attempting to rebuild in $(OPENCM3_DIR))
	$(MAKE) -C $(OPENCM3_DIR) TARGETS='stm32/f4'

%.elf: $(OBJS) $(LDSCRIPT) $(OPENCM3_DIR)/lib/lib$(LIBNAME).a
	@printf "  LD      $@\n"
	$(Q)$(LD) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

$(BOOTLOADER_DIR)/bootloader.bin:
	$(warning $@ not found, attempting to rebuild in $(BOOTLOADER_DIR))
	$(MAKE) -C $(BOOTLOADER_DIR)

$(SRC_DIR)/bootloader.o: $(SRC_DIR)/bootloader.S $(BOOTLOADER_DIR)/bootloader.bin
	@printf "  CC      $<\n"
	$(Q)$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.c
	@printf "  CC      $<\n"
	$(Q)$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.S
	@#printf "  CC      $(*).S\n"
	$(Q)$(CC) $(CFLAGS) -o $@ -c $	$(Q)@echo "Building $@ from $<."

%.o: %.cxx
	@printf "  CXX     $<\n"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ -c $<

%.o: %.cpp
	@printf "  CXX     $<\n"
	$(Q)$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	$(Q)$(RM) -rf $(TARGET_NAME).* generated.* $(OBJS) $(OBJS:%.o=%.d)
	$(Q)$(MAKE) -C $(BOOTLOADER_DIR) clean

.PHONY: all clean images

-include $(OBJS:.o=.d)