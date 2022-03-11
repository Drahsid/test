#include <ultra64.h>
#include "inttypes.h"

#define BOOTSTACKSIZE 0x1000
u32 gDeadBeef;
const SIZE_TYPE gBootStackSize = BOOTSTACKSIZE;
u8 gBootStack[BOOTSTACKSIZE];

u64 gTimer;

void main(void) {
    gDeadBeef = 0xDEADBEEF;

    osInitialize();

    osViBlack(1);
    osViSetMode(&osViModeTable[OS_VI_PAL_HAN1]);
    osViBlack(0);

    while(1) {
        gTimer++;
    }
}
