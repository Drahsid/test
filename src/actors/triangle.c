#include "actors/triangle.h"
#include "usb/debug.h"

#define ACTOR_SEGMENT_OFFSET(__MEMBER__) ((SEGMENT_ACTOR << 24) | OFFSETOF(Actor_Triangle, __MEMBER__))

static Vtx sTriangleVtx[] = {
    {-64,  64, -5, 0, 0, 0, 0, 0xff, 0, 0xff},
    { 64,  64, -5, 0, 0, 0, 0, 0, 0, 0xff},
    { 64, -64, -5, 0, 0, 0, 0, 0, 0xff, 0xff},
    {-64, -64, -5, 0, 0, 0, 0xff, 0, 0, 0xff},
};

static Gfx sTriangleGfx[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPVertex(&(sTriangleVtx[0]), 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList()
};

static Vec3 sSpawnPos = { 0, 0, 15.0f };

void Actor_Triangle_Step(Actor_Triangle* thisx, GlobalCtx* global) {
    thisx->actor.rot.roll += 1.0f;
    //thisx->actor.pos.z = 15.0f + (cosf(global->gfxCtx.time) * 15.0f);
}

void Actor_Triangle_Draw(Actor_Triangle* thisx, GlobalCtx* global) {
    gSPDisplayList(global->gfxCtx.dlist++, sTriangleGfx);
}

void Actor_Triangle_Construct(Actor_Triangle* thisx, GlobalCtx* global) {
    Actor_SetPosition(thisx, &sSpawnPos);
    thisx->actor.scale = 0.1f;
}

void Actor_Triangle_Deconstruct(Actor_Triangle* thisx, GlobalCtx* global) {
}

ActorInit gActorInit_TriangleActor = {
    .step = Actor_Triangle_Step,
    .draw = Actor_Triangle_Draw,
    .ctor = Actor_Triangle_Construct,
    .dtor = Actor_Triangle_Deconstruct,
    .size = sizeof(Actor_Triangle)
};

