# some test thing
Testing n64 homebrew stuff?

## Building
You must create a `lib` folder and populate it with the following files:
- boot.6102
- gspF3DEX2.fifo.o
- rspboot.o

Furthermore, you must compile libultra with -mabi-n32, and place the outputs as
- libultra_d_n32.a
- libultra_rom_n32.a

Then simply run `make`.
