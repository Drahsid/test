@echo off
echo TOOLS TOOLS TOOLS TOOLS TOOLS TOOLS TOOLS TOOLS TOOLS TOOLS
call make_tools.cmd 1
echo TOOLS TOOLS TOOLS TOOLS TOOLS TOOLS TOOLS TOOLS TOOLS TOOLS

set rpg64_abi=eabi
call make_clean.cmd 1
call make_ultralib.cmd 1
call make.cmd 1
move build/rpg64_eabi.z64 rpg64_eabi.z64

@echo on
