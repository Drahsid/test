#ifndef ACTORCTX_H
#define ACTORCTX_H

typedef struct {
    struct Actor* first;
    struct Actor* last;
} ActorCtx;

extern void ActorCtx_Construct(ActorCtx* thisx);
extern void ActorCtx_ActorRemove(ActorCtx* thisx, struct Actor* actor);
extern void ActorCtx_ActorAdd(ActorCtx* thisx, struct Actor* actor);

#endif

