#ifndef ACTOR_H
#define ACTOR_H

#include "common.h"
#include "GlobalCtx.h"

typedef void(*ActorFunc)(struct Actor* thisx, GlobalCtx* global);

typedef struct Actor_t {
    Vec3 pos;
    Rot3 rot;
    float scale;
    Vec3 scaleXYZ;
    Mtx mtxTranslate;
    Mtx mtxRotate;
    Mtx mtxScale;
    ActorFunc step;
    ActorFunc draw;
    ActorFunc ctor;
    ActorFunc dtor;
    struct Actor_t* prev;
    struct Actor_t* next;
} Actor;

typedef struct {
    ActorFunc step;
    ActorFunc draw;
    ActorFunc ctor;
    ActorFunc dtor;
    SIZE_TYPE size;
} ActorInit;

extern void Actor_Construct(Actor* thisx);
extern void Actor_Init(GlobalCtx* global, ActorInit* init, Actor* thisx);
extern Actor* Actor_Spawn(GlobalCtx* global, ActorInit* init);
extern void Actor_Destroy(Actor* thisx, GlobalCtx* global);
extern void Actor_SetPosition(Actor* thisx, Vec3* pos);
extern void Actor_SetRotation(Actor* thisx, Rot3* rot);
extern void Actor_SetScaleXYZ(Actor* thisx, Vec3* scale);
extern void Actor_DummyActorFunc(Actor* thisx, GlobalCtx* global);
extern void Actor_StepAll(GlobalCtx* global);
extern void Actor_DrawAll(GlobalCtx* global);

#endif

