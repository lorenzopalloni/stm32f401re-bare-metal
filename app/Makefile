# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
Q := @
endif

# Useful variables
DEVICE          = stm32f401re
OPENCM3_DIR     = ../libopencm3
INC_DIR 		= inc
SRC_DIR         = src
SHARED_INC_DIR  = ../shared/inc
SHARED_SRC_DIR  = ../shared/src

# Source files
OBJS            += ${SRC_DIR}/firmware.o
OBJS 			+= ${SHARED_SRC_DIR}/core/uart.o
OBJS 			+= ${SHARED_SRC_DIR}/core/system.o

# C Flags
CFLAGS          += -Os -ggdb3

# C++ Flags
INCS			+= -I$(INC_DIR) -I$(SHARED_INC_DIR)
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
	$(Q)$(RM) -rf binary.* $(SRC_DIR)/*.o $(SRC_DIR)/*.d generated.* $(SHARED_SRC_DIR)/*.o $(SHARED_SRC_DIR)/*.d

include $(OPENCM3_DIR)/mk/genlink-rules.mk
include $(OPENCM3_DIR)/mk/gcc-rules.mk
