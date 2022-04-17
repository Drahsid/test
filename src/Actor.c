#include "Actor.h"

#include "segments.h"
#include "usb/debug.h"

#define ACTOR_SEGMENT_OFFSET(__MEMBER__) ((SEGMENT_ACTOR << 24) | OFFSETOF(Actor, __MEMBER__))

void Actor_Construct(Actor* thisx) {
    thisx->pos.x = 0;
    thisx->pos.y = 0;
    thisx->pos.z = 0;
    thisx->rot.pitch = 0;
    thisx->rot.yaw = 0;
    thisx->rot.roll = 0;
    thisx->scale = 1.0f;
    thisx->scaleXYZ.x = 1.0f;
    thisx->scaleXYZ.y = 1.0f;
    thisx->scaleXYZ.z = 1.0f;
    guMtxIdent(&thisx->mtxTranslate);
    guMtxIdent(&thisx->mtxRotate);
    guMtxIdent(&thisx->mtxScale);
}

void Actor_Init(GlobalCtx* global, ActorInit* init, Actor* thisx) {
    thisx->step = init->step;
    thisx->draw = init->draw;
    thisx->ctor = init->ctor;
    thisx->dtor = init->dtor;
    thisx->ctor(thisx, global);
}

Actor* Actor_Spawn(GlobalCtx* global, ActorInit* init) {
    Actor* actor = NULLPTR;
    
    if (init == NULLPTR) {
        debug_printf("Error: [Actor_Spawn] init is null\n");
        return NULLPTR;
    }
    
    actor = malloc(init->size);

    if (actor == NULLPTR) {
        debug_printf("Error: [Actor_Spawn] Actor failed to allocate!\n");
        return NULLPTR;
    }

    memset_u32(actor, 0, sizeof(Actor));
    Actor_Construct(actor);
    Actor_Init(global, init, actor);
    ActorCtx_ActorAdd(&global->actorCtx, actor);

    return actor;
}


void Actor_Destroy(Actor* thisx, GlobalCtx* global) {
    thisx->dtor(thisx, global);
    ActorCtx_ActorRemove(&global->actorCtx, thisx);
    free(thisx);
}

void Actor_SetPosition(Actor* thisx, Vec3* pos) {
    thisx->pos.x = pos->x;
    thisx->pos.y = pos->y;
    thisx->pos.z = pos->z;
}

void Actor_SetRotation(Actor* thisx, Rot3* rot) {
    thisx->rot.x = rot->x;
    thisx->rot.y = rot->y;
    thisx->rot.z = rot->z;
}

void Actor_SetScaleXYZ(Actor* thisx, Vec3* scale) {
    thisx->scaleXYZ.x = scale->x;
    thisx->scaleXYZ.y = scale->y;
    thisx->scaleXYZ.z = scale->z;
}

void Actor_DummyActorFunc(Actor* thisx, GlobalCtx* global) {}


void Actor_StepAll(GlobalCtx* global) {
    Actor* actor = global->actorCtx.first;

    while (actor != NULLPTR) {
        if (actor->step != NULLPTR) {
            actor->step(actor, global);
        }
        actor = actor->next;
    }
}

void Actor_DrawAll(GlobalCtx* global) {
    Actor* actor = global->actorCtx.first;

    while (actor != NULLPTR) {
        if (actor->draw != NULLPTR) {
            // setup matrixes
            guTranslate(&actor->mtxTranslate, actor->pos.x, actor->pos.y, actor->pos.z);
            guRotateRPY(&actor->mtxRotate, RTOD(actor->rot.roll), RTOD(actor->rot.pitch), RTOD(actor->rot.yaw));
            guScale(&actor->mtxScale, actor->scaleXYZ.x * actor->scale, actor->scaleXYZ.y * actor->scale, actor->scaleXYZ.z * actor->scale);

            // setup segment and push matrixes
            gSPSegment(global->gfxCtx.dlist++, SEGMENT_ACTOR, actor);
            gSPMatrix(global->gfxCtx.dlist++, ACTOR_SEGMENT_OFFSET(mtxTranslate), G_MTX_MODELVIEW | G_MTX_PUSH | G_MTX_MUL);
            gSPMatrix(global->gfxCtx.dlist++, ACTOR_SEGMENT_OFFSET(mtxRotate), G_MTX_MODELVIEW | G_MTX_NOPUSH | G_MTX_MUL);
            gSPMatrix(global->gfxCtx.dlist++, ACTOR_SEGMENT_OFFSET(mtxScale), G_MTX_MODELVIEW | G_MTX_NOPUSH | G_MTX_MUL);
            actor->draw(actor, global);
            // pop matrixes
            gSPPopMatrix(global->gfxCtx.dlist++, G_MTX_MODELVIEW);
            gDPPipeSync(global->gfxCtx.dlist++);
        }
        
        actor = actor->next;
    }
}
