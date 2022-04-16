#ifndef ACTOR_TRIANGLE_H
#define ACTOR_TRIANGLE_H

#include "common.h"
#include "Actor.h"

typedef struct {
    Actor actor;
    u32 deadbeef;
    OSTime ticks;
} Actor_Triangle;

extern ActorInit gActorInit_TriangleActor;

#endif

