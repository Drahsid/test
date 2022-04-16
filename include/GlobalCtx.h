#ifndef GLOBALCTX_H
#define GLOBALCTX_H

#include "common.h"
#include "GfxCtx.h"
#include "Heap.h"
#include "ActorCtx.h"
#include "Camera.h"

typedef struct {
    GfxCtx gfxCtx;
    Heap heap;
    ActorCtx actorCtx;
    Camera camera;
} GlobalCtx;

extern GlobalCtx gGlobalCtx;
extern GlobalCtx* gpGlobalCtx;

extern void GlobalCtx_Construct(GlobalCtx* thisx);

#endif

