#include "framebuffer.h"

u16* gFramebuffer[FRAMEBUFFER_COUNT + 1] = {
    gFramebuffer0, gFramebuffer1, gFramebuffer2
};

FRAMEBUFFER_SECTION(0) u16 gFramebuffer0[BASE_RES_Y * BASE_RES_X];
FRAMEBUFFER_SECTION(1) u16 gFramebuffer1[BASE_RES_Y * BASE_RES_X];
FRAMEBUFFER_SECTION(2) u16 gFramebuffer2[BASE_RES_Y * BASE_RES_X]; // z
