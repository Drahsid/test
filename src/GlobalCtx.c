#include "GlobalCtx.h"
#include "usb/debug.h"

GlobalCtx gGlobalCtx;
GlobalCtx* gpGlobalCtx = &gGlobalCtx;

#define SAFETY_PADDING (0x40)

void GlobalCtx_Construct(GlobalCtx* thisx) {
    SIZE_TYPE heap_start = __stack_end;
    SIZE_TYPE heap_size = NULL;
    SIZE_TYPE mem_size = osGetMemSize();

    gpGfxCtx = &thisx->gfxCtx;
    gpHeap = &thisx->heap;

    osCreateViManager(OS_PRIORITY_VIMGR);

    if (mem_size < 0x00800000) {
        debug_printf("LOW MEMORY PRESENT! %X DETECTED\n", mem_size);
        Framebuffer_SetLowMem();
        heap_size = ((SIZE_TYPE)__framebuffer_lowmem_start - (SIZE_TYPE)__stack_end) - SAFETY_PADDING;
    }
    else if (mem_size > 0x00800000) {
        debug_printf("[emulator] CRAZY MEMORY PRESENT! %X DETECTED\n", mem_size);
        FrameBuffer_SetHiRes();
        heap_size = (mem_size - 0x00800000) - SAFETY_PADDING;
        heap_start = 0x80800000;
    }
    else {
        debug_printf("HIGH MEMORY PRESENT! %X DETECTED\n", mem_size);
        FrameBuffer_SetHiRes();
        heap_size = ((SIZE_TYPE)__framebuffer_start - (SIZE_TYPE)__stack_end) - SAFETY_PADDING;
    }

    memset_u32(thisx, 0, sizeof(GlobalCtx));
    memset_u32(heap_start, 'heap', heap_size);
    Heap_Construct(&thisx->heap, heap_start, heap_size);
    debug_printf("Heap_Constructed at %X with size %X (%.2f MB)\n", heap_start, heap_size, (f32)heap_size / 1024.0f / 1024.0f);

    GfxCtx_Construct(&thisx->gfxCtx);
    debug_printf("GfxCtx_Constructed.. ");
    
    ActorCtx_Construct(&thisx->actorCtx);
    debug_printf("ActorCtx_Construct... \n");

    //ControllerCtx_Construct(&thisx->controllerCtx);
}

