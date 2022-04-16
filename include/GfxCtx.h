#ifndef GFXCTX_H
#define GFXCTX_H

#include "common.h"
#include "framebuffer.h"
#include "segments.h"

#define RDPFIFO_SIZE (4096 * 16)

typedef struct {
    OSMesgQueue rspMessageQ;
    OSMesgQueue rdpMessageQ;
    OSMesgQueue retraceMessageQ;
    OSMesg rspMessageBuf;
    OSMesg rdpMessageBuf;
    OSMesg retraceMessageBuf;
    OSTask taskList;
    u64 rdpFifo[RDPFIFO_SIZE];
    u8 rspYield[OS_YIELD_DATA_SIZE];
    u8 framebufferIndex;
    Gfx* glist[FRAMEBUFFER_COUNT];
    Gfx* dlist;
    Vp viewport;
    Mtx projection;
    Mtx view;
    u64 frames;
    u64 frameclocks;
    f32 time;
    f32 frametime;
    f32 framerate;
} GfxCtx;

extern GfxCtx* gpGfxCtx;

extern Gfx gClearCFB[];

extern void GfxCtx_Construct(GfxCtx* thisx);
extern void GfxCtx_GfxBegin(GfxCtx* thisx);
extern void GfxCtx_GfxEnd(GfxCtx* thisx);
extern void GfxCtx_GfxSendTask(GfxCtx* thisx);
extern void GfxCtx_GfxRetrace(GfxCtx* thisx);

#endif

