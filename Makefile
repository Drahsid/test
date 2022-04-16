CROSS = mips64-
AS = $(CROSS)as
CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
OBJCOPY = $(CROSS)objcopy
PYTHON = python3
N64CRC = $(TOOLS_DIR)/n64crc

PROJECTNAME = rpg64

BUILD_DIR = build
TOOLS_DIR = tools

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
LIB_DIR = lib

SRC_DIRS = $(SRC_DIR) $(SRC_DIR)/usb $(SRC_DIR)/actors
ASM_DIRS = $(SRC_DIR)/asm
BIN_DIRS = $(BIN_DIR)
INCLUDE_DIRS = -I$(INC_DIR) -Iultralib/include -I$(MIPS64_LIBGCCDIR)/include -I$(MIPS64_LIBCDIR)/include

S_FILES   = $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
C_FILES   = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
BIN_FILES = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
O_FILES = $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)

ABI ?= eabi
RELEASE_BUILD ?= 1

ifeq ($(ABI),eabi)
REG_FLAGS = -mgp32 -mfp32
#LD_ABI = -m elf32btsmip
endif

ifeq ($(ABI),n32)
#LD_ABI = -m elf32btsmipn32
endif

ifeq ($(ABI),32)
#LD_ABI = -m elf32btsmip
ULTRA_PRE:=o
endif

GBI_DEFINE = -DF3DEX_GBI_2
CDEF_FLAGS = -D_LANGUAGE_C -D_MIPS_SZLONG=32 $(GBI_DEFINE)
ADEF_FLAGS = -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64
ABI_FLAG = -mabi=$(ABI)
ARCH_FLAGS = -mips3 -mtune=vr4300 -march=vr4300

ifeq ($(RELEASE_BUILD),1)
OPT_FLAGS = -Os
OPT_FLAGS2 := -mfix4300 -mno-check-zero-division -mframe-header-opt -fno-inline-functions -falign-functions=32 -fwrapv -fmerge-all-constants -ffast-math
CDEF_FLAGS += -D_FINALROM -DNDEBUG
ULTRA_LIB = -lgultra_rom_$(ULTRA_PRE)$(ABI)
DEBUG_BUILD=0
else
OPT_FLAGS = -g3
OPT_FLAGS2 := -mfix4300 -mno-check-zero-division -mframe-header-opt -fno-inline-functions -falign-functions=64 -fwrapv -fmerge-all-constants -fno-stack-protector -fmodulo-sched -fmodulo-sched-allow-regmoves -fira-hoist-pressure -fweb -floop-interchange -fsplit-paths -fallow-store-data-races
CDEF_FLAGS += -DDEBUG
ULTRA_LIB = -lgultra_d_$(ULTRA_PRE)$(ABI)
DEBUG_BUILD=1
endif

TARGET = $(BUILD_DIR)/$(PROJECTNAME)_$(ULTRA_PRE)$(ABI)
ROMSIZE = 0x00200000
CC_FLAGS = -G 0 -nostdlib -nostdinc $(OPT_FLAGS) $(OPT_FLAGS2) $(ABI_FLAG) $(CDEF_FLAGS) $(REG_FLAGS) $(ARCH_FLAGS) -mno-shared -mno-abicalls -fno-common -fno-PIC -ffreestanding -Wall -Wno-missing-braces -Wno-incompatible-pointer-types -Wno-int-conversion -Wno-pointer-sign $(INCLUDE_DIRS)
AS_FLAGS = -EB $(OPT_FLAGS) $(ABI_FLAG) $(REG_FLAGS) $(ARCH_FLAGS)
LD_FLAGS = -T $(PROJECTNAME)_$(ABI).ld -Map $(TARGET).map --accept-unknown-input-arch --no-check-sections -L$(MIPS64_LIBCDIR)/lib -L$(MIPS64_LIBGCCDIR) -L$(LIB_DIR) $(ULTRA_LIB) $(LD_ABI) -lgcc -lc
OBJCOPY_FLAGS = --pad-to $(ROMSIZE) --gap-fill 0xFF -O binary

default: dirs $(TARGET).z64

dirs:
	$(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

clean:
	rm -rf $(BUILD_DIR)

tools:
	make -C $(TOOLS_DIR)

ultralib:
	make -C ultralib distclean
	make -C ultralib clean
	make -C ultralib setup
	make -C ultralib ABI=$(ABI) DEBUG_BUILD=$(DEBUG_BUILD) USE_MODERN_GCC=1
ifeq ($(RELEASE_BUILD),1)
	cp -f ultralib/build/libgultra_rom_$(ULTRA_PRE)$(ABI).a $(LIB_DIR)
else
	cp -f ultralib/build/libgultra_d_$(ULTRA_PRE)$(ABI).a $(LIB_DIR)
endif

$(BUILD_DIR)/boot.6102.o: $(LIB_DIR)/boot.6102
	$(OBJCOPY) -I binary -O elf32-big $< $@

$(BUILD_DIR)/%.c.o: %.c
	$(CC) -c $(CC_FLAGS) -o $@ $<

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<

$(TARGET).elf: dirs tools $(O_FILES) $(BUILD_DIR)/boot.6102.o
	$(LD) $(O_FILES) -o $@ $(LD_FLAGS)

$(TARGET).z64: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@
	$(N64CRC) $@

.SECONDARY:
.PHONY: clean default dirs tools ultralib
SHELL = /bin/bash -e -o pipefail

