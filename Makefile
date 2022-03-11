CROSS = mips-linux-gnu-
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

SRC_DIRS = $(SRC_DIR)
ASM_DIRS = $(SRC_DIR)/asm
BIN_DIRS = $(BIN_DIR)
INCLUDE_DIRS = -I$(INC_DIR) -Iultralib/include

S_FILES   = $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
C_FILES   = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
BIN_FILES = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
O_FILES = $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)

TARGET = $(BUILD_DIR)/$(PROJECTNAME)

GBI_DEFINE = -DF3DEX_GBI_2
CDEF_FLAGS = -D_LANGUAGE_C -D_MIPS_SZLONG=32 $(GBI_DEFINE)
ADEF_FLAGS = -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64
ABI = -mabi=n32

ifdef RELEASE_BUILD
OPT_FLAGS = -Os
CDEF_FLAGS += -D_FINALROM -DNDEBUG
ULTRA_LIB = -lultra_rom_n32
else
OPT_FLAGS = -g3
CDEF_FLAGS += -DDEBUG
ULTRA_LIB = -lultra_d_n32
endif

ROMSIZE = 0x400000

CC_FLAGS = -G 0 -nostdinc $(OPT_FLAGS) $(ABI) -mips3 -mtune=vr4300 -march=vr4300 -mno-abicalls -mno-check-zero-division -fno-stack-protector -ffreestanding $(INCLUDE_DIRS)
AS_FLAGS = -EB $(OPT_FLAGS) $(ABI) -mips3 -mtune=vr4300 -march=vr4300
LD_FLAGS = -T $(PROJECTNAME).ld -Map $(TARGET).map --accept-unknown-input-arch --no-check-sections -L$(LIB_DIR) $(ULTRA_LIB) -m elf32btsmipn32
OBJCOPY_FLAGS = --pad-to $(ROMSIZE) --gap-fill 0xFF -O binary

default: dirs $(TARGET).z64

dirs:
	$(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

clean:
	rm -rf $(BUILD_DIR)

tools:
	make -C $(TOOLS_DIR)

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
.PHONY: clean default
SHELL = /bin/bash -e -o pipefail

