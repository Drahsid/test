#include "Camera.h"

void Camera_Vec3Normalize(Vec3* dest, Vec3* lhs) {
    float magnitude = sqrtf((lhs->x * lhs->x) + (lhs->y * lhs->y) + (lhs->z * lhs->z));
    if (magnitude == 0) {
        dest->x = dest->y = dest->z = 0;
    }
    else {
        dest->x = lhs->x / magnitude;
        dest->y = lhs->y / magnitude;
        dest->z = lhs->z / magnitude;
    }
}

void Camera_Vec3Cross(Vec3* dest, Vec3* lhs, Vec3* rhs) {
    dest->x = lhs->y * rhs->z - rhs->y * lhs->z;
    dest->y = lhs->z * rhs->x - rhs->z * lhs->x;
    dest->z = lhs->x * rhs->y - rhs->x * lhs->y;
}

float Camera_Vec3Dot(Vec3* lhs, Vec3* rhs) {
    return (lhs->x * rhs->x) + (lhs->y * rhs->y) + (lhs->z * rhs->z);
}

void Camera_PositionLookF(Camera* thisx, MtxF mf) {
    u32 index;
    Vec3 backward;

    guMtxIdentF(mf);

    backward.x = -thisx->forward.x;
    backward.y = -thisx->forward.y;
    backward.z = -thisx->forward.z;

    for (index = 0; index < 3; index++) {
        mf[index][0] = thisx->right.xyz[index];
        mf[index][1] = thisx->up.xyz[index];
        mf[index][2] = backward.xyz[index];
    }

    mf[3][0] = -Camera_Vec3Dot(&thisx->right, &thisx->pos);
    mf[3][1] = -Camera_Vec3Dot(&thisx->up, &thisx->pos);
    mf[3][2] = -Camera_Vec3Dot(&backward, &thisx->pos);

    mf[0][3] = 0;
	mf[1][3] = 0;
	mf[2][3] = 0;
    mf[3][3] = 1.0f;
}

void Camera_PositionLook(Camera* thisx, Mtx* m) {
    MtxF mf;
    Camera_PositionLookF(thisx, mf);
    guMtxF2L(mf, m);
}

void Camera_ApplyEuler(Camera* thisx, Rot3* rot) {
    Vec3 right = { 1, 0, 0 };
    Vec3 up = { 0, 1, 0 };
    Vec3 forward = { 0, 0, 1 };

    forward.x = cosf(rot->x) * cosf(rot->y);
    forward.y = -sinf(rot->x);
    forward.z = cosf(rot->x) * sinf(rot->y);

    Camera_Vec3Cross(&right, &forward, &up);

    up.x = cosf(rot->x - MATH_HPI) * cosf(rot->y);
    up.y = -sinf(rot->x - MATH_HPI);
    up.z = cosf(rot->x - MATH_HPI) * sinf(rot->y);

    Camera_Vec3Normalize(&right, &right);
    Camera_Vec3Normalize(&up, &up);
    Camera_Vec3Normalize(&forward, &forward);
}

