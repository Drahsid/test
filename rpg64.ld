OUTPUT_ARCH (mips)
EXTERN (entrypoint)
ENTRY (entrypoint)

SECTIONS {
    __rom_offset = 0;

    .boot 0xA4000000 : AT(__rom_offset) {
        KEEP(build/src/asm/header.s.o(.data));
        KEEP(build/boot.6102.o);
    }
    __rom_offset += SIZEOF(.boot);

    __code_start = ADDR(.code);
    __code_start_rom = __rom_offset;
    .code 0x80000400 : AT(__rom_offset) ALIGN(64) SUBALIGN(64) {
        KEEP(build/src/asm/entrypoint.s.o);
#        lib/rspboot.o(.text);
#        lib/gspF3DEX2.fifo.o(.text);
        *(.text);

#        lib/rspboot.o(.rodata);
#        lib/gspF3DEX2.fifo.o(.rodata);
        *(.rodata)

#        lib/rspboot.o(.data);
#        lib/gspF3DEX2.fifo.o(.data);
        *(.data)
    }
    __code_end  = ADDR(.code) + SIZEOF(.code);
    __code_size = SIZEOF(.code);
    __rom_offset += SIZEOF(.code);

    __bss_start = ADDR(.bss);
    .bss (NOLOAD) : ALIGN(64) SUBALIGN(64) {
#        lib/rspboot.o(.bss);
#        lib/gspF3DEX2.fifo.o(.bss);

        *(COMMON);
        *(.scommon);
        *(.bss);
    }
    __bss_end = ADDR(.bss) + SIZEOF(.bss);
    __bss_size = SIZEOF(.bss);
    __rom_offset += SIZEOF(.bss);

    /DISCARD/ : {
      *(*);
   }
}

