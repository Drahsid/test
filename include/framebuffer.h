#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "common.h"

#define BASE_RES_X 640
#define BASE_RES_Y 480

#define RES_HIRES_X (BASE_RES_X)
#define RES_HIRES_Y (BASE_RES_Y)
#define RES_LORES_X (BASE_RES_X / 2)
#define RES_LORES_Y (BASE_RES_Y / 2)

#define FRAMEBUFFER_COUNT 2

enum {
    FRAMEBUFFER_INDEX_0 = 0,
    FRAMEBUFFER_INDEX_1,
    FRAMEBUFFER_INDEX_Z
};

extern u16* gFramebuffer[FRAMEBUFFER_COUNT + 1];
extern u16 gScreenResX;
extern u16 gScreenResY;
extern float gScreenResRatio;

extern void Framebuffer_SetLowMem(void);
extern void FrameBuffer_SetLoRes(void);
extern void FrameBuffer_SetHiRes(void);

#endif

