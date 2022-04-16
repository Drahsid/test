#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

typedef struct {
    Vec3 pos;
    Vec3 right;
    Vec3 up;
    Vec3 forward;
} Camera;

extern void Camera_PositionLookF(Camera* thisx, MtxF mf);
extern void Camera_PositionLook(Camera* thisx, Mtx* m);
extern void Camera_ApplyEuler(Camera* thisx, Rot3* rot);

#endif
