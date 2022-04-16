#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "common.h"

#define BASE_RES_X 640
#define BASE_RES_Y 480
#define FRAMEBUFFER_COUNT 2

#define FRAMEBUFFER_SECTION(NUM) __attribute__((section(".framebuffer." #NUM)))

extern u16* gFramebuffer[FRAMEBUFFER_COUNT + 1];
extern u16 gFramebuffer0[BASE_RES_Y * BASE_RES_X];
extern u16 gFramebuffer1[BASE_RES_Y * BASE_RES_X];
extern u16 gFramebuffer2[BASE_RES_Y * BASE_RES_X]; // z

#endif

