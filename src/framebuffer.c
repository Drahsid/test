#include "framebuffer.h"

#define FRAMEBUFFER_SECTION(NUM) __attribute__((section(".framebuffer." #NUM)))
#define FRAMEBUFFER_LOWMEM_SECTION(NUM) __attribute__((section(".framebuffer_lowmem." #NUM)))

FRAMEBUFFER_SECTION(0) u16 gFramebuffer0[RES_HIRES_Y * RES_HIRES_X];
FRAMEBUFFER_SECTION(1) u16 gFramebuffer1[RES_HIRES_Y * RES_HIRES_X];
FRAMEBUFFER_SECTION(2) u16 gFramebuffer2[RES_HIRES_Y * RES_HIRES_X]; // z

FRAMEBUFFER_LOWMEM_SECTION(0) u16 gFramebuffer_LowMem_0[RES_LORES_Y * RES_LORES_X];
FRAMEBUFFER_LOWMEM_SECTION(1) u16 gFramebuffer_LowMem_1[RES_LORES_Y * RES_LORES_X];
FRAMEBUFFER_LOWMEM_SECTION(2) u16 gFramebuffer_LowMem_2[RES_LORES_Y * RES_LORES_X]; // z

u16* gFramebuffer[FRAMEBUFFER_COUNT + 1] = {
    gFramebuffer0, gFramebuffer1, gFramebuffer2
};

u16 gScreenResX = RES_HIRES_X;
u16 gScreenResY = RES_HIRES_Y;
float gScreenResRatio = 1.0f;

void Framebuffer_SetLowMem() {
    gFramebuffer[0] = gFramebuffer_LowMem_0;
    gFramebuffer[1] = gFramebuffer_LowMem_1;
    gFramebuffer[2] = gFramebuffer_LowMem_2;
    FrameBuffer_SetLoRes();
}

void FrameBuffer_SetLoRes() {
    gScreenResX = RES_LORES_X;
    gScreenResY = RES_LORES_Y;
    gScreenResRatio = 0.5f;

    if (osTvType == OS_TV_NTSC) {
        osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);
    }
    else if (osTvType == OS_TV_PAL) {
        osViSetMode(&osViModeTable[OS_VI_PAL_LAN1]);
    }
    else if (osTvType == OS_TV_MPAL) {
        osViSetMode(&osViModeTable[OS_VI_MPAL_LAN1]);
    }
}

void FrameBuffer_SetHiRes() {
    gScreenResX = RES_HIRES_X;
    gScreenResY = RES_HIRES_Y;
    gScreenResRatio = 1.0f;
    
    if (osTvType == OS_TV_NTSC) {
        osViSetMode(&osViModeTable[OS_VI_NTSC_HAN1]);
    }
    else if (osTvType == OS_TV_PAL) {
        osViSetMode(&osViModeTable[OS_VI_PAL_HAN1]);
    }
    else if (osTvType == OS_TV_MPAL) {
        osViSetMode(&osViModeTable[OS_VI_MPAL_HAN1]);
    }

}
