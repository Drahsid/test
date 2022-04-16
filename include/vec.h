#ifndef VEC_H
#define VEC_H

typedef struct {
    float x;
} Vec1;

typedef struct {
    float x;
    float y;
} Vec2;

typedef union {
    struct {
        float x;
        float y;
        float z;
    };
    float xyz[3];
} Vec3;

typedef union {
    struct {
        float x;
        float y;
        float z;
    };
    struct {
        float pitch;
        float yaw;
        float roll;
    };
} Rot3;

typedef float MtxF[4][4];

#endif
