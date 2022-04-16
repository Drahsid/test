#include "ActorCtx.h"
#include "Actor.h"

void ActorCtx_Construct(ActorCtx* thisx) {
    thisx->first = NULLPTR;
    thisx->last = NULLPTR;
}

void ActorCtx_ActorRemove(ActorCtx* thisx, struct Actor* actor) {
    Actor* rhs = thisx->first;

    if (thisx->first == actor) {
        if (thisx->last == actor) {
            // if first and last in the list
            thisx->first = thisx->last = NULLPTR;
        }
        else {
            // if first in the list
            ((Actor*)rhs->next)->prev = NULLPTR;
            thisx->first = rhs->next;
        }

        return;
    }

    while (rhs) {
        if (rhs == actor) {
            if (rhs->next) {
                if (rhs->prev) {
                    // if somewhere in the middle of the list
                    ((Actor*)rhs->prev)->next = rhs->next;
                    ((Actor*)rhs->next)->prev = rhs->prev;
                }
            }
            else {
                // if at the end of the list
                ((Actor*)rhs->prev)->next = NULLPTR;
                thisx->last = rhs->prev;
            }
            return;
        }

        rhs = rhs->next;
    }
}

void ActorCtx_ActorAdd(ActorCtx* thisx, struct Actor* actor) {
    if (thisx->last == NULLPTR) {
        thisx->first = actor;
    }
    else {
        ((Actor*)thisx->last)->next = actor;
        ((Actor*)actor)->prev = thisx->last;
    }

    thisx->last = actor;
    ((Actor*)actor)->next = NULLPTR;
}

