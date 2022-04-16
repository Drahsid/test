#include "GlobalCtx.h"
#include "usb/debug.h"
#include "linker_symbols.h"

GlobalCtx gGlobalCtx;
GlobalCtx* gpGlobalCtx = &gGlobalCtx;

void GlobalCtx_Construct(GlobalCtx* thisx) {
    gpGfxCtx = &thisx->gfxCtx;
    gpHeap = &thisx->heap;

    memset_u8(thisx, 0, sizeof(GlobalCtx));

    Heap_Construct(&thisx->heap, __stack_end, (SIZE_TYPE)__framebuffer_start - (SIZE_TYPE)__stack_end);
    debug_printf("Heap_Construct. ");

    GfxCtx_Construct(&thisx->gfxCtx);
    debug_printf("GfxCtx_Construct.. ");
    
    ActorCtx_Construct(&thisx->actorCtx);
    debug_printf("ActorCtx_Construct... \n");
}

