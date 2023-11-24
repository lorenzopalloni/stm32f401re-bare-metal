# Useful variables
INC_DIR 		= inc
SRC_DIR         = src
DEVICE          = stm32f401re
OPENCM3_DIR     = ../libopencm3

# Source files
OBJS            += ${SRC_DIR}/firmware.o
OBJS 			+= ${SRC_DIR}/uart.o

# C Flags
CFLAGS          += -Os -ggdb3

# C++ Flags
# INCS			+= -I$(OPENCM3_DIR)/include
INCS			+= -I$(INC_DIR)
CPPFLAGS		+= -MD
CPPFLAGS 		+= $(INCS)

# Linkerscript
LDFLAGS         += -static -nostartfiles
LDLIBS          += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/mk/gcc-config.mk

.PHONY: clean all

all: binary.elf binary.hex

clean:
	$(Q)$(RM) -rf binary.* $(SRC_DIR)/*.o $(SRC_DIR)/*.d generated.*

include $(OPENCM3_DIR)/mk/genlink-rules.mk
include $(OPENCM3_DIR)/mk/gcc-rules.mk