#ifndef COMMON_H
#define COMMON_H

#include <ultra64.h>
#include "inttypes.h"
#include "libc.h"
#include "vec.h"
#include "linker_symbols.h"

#define DATA_ALIGN64 __attribute__((aligned(64)))
#define DATA_ALIGN32 __attribute__((aligned(32)))
#define DATA_ALIGN16 __attribute__((aligned(16)))

#define OFFSETOF(TYPE, ELEMENT) ((SIZE_TYPE)&(((TYPE*)0)->ELEMENT))

#define MATH_PI (3.14159265358979323)
#define MATH_TAU (MATH_PI * 2.0)
#define MATH_HPI (MATH_PI * 0.5)

#define DEG2RAD (0.0174532925199433)
#define RAD2DEG (57.29577951308231)
#define S2RAD (0.0000958737992429)
#define S2DEG (0.0054931640625)
#define RAD2S (10430.37835047045)
#define DEG2S (182.0444444444444)

// My math could be wrong here
#define C2SEC (1.06666666e-8)
#define C2MSEC (0.00001066666)

#define STOR(RHS) (S2RAD * RHS)
#define STOD(RHS) (S2DEG * RHS)
#define RTOS(RHS) (RAD2S * RHS)
#define DTOS(RHS) (DEG2S * RHS)
#define DTOR(RHS) (DEG2RAD * RHS)
#define RTOD(RHS) (RAD2DEG * RHS)

// If you ever need to explicitly truncate these
#define STORF(RHS) ((float)S2RAD * RHS)
#define STODF(RHS) ((float)S2DEG * RHS)
#define RTOSF(RHS) ((float)RAD2S * RHS)
#define DTOSF(RHS) ((float)DEG2S * RHS)
#define DTORF(RHS) ((float)DEG2RAD * RHS)
#define RTODF(RHS) ((float)RAD2DEG * RHS)

#define OS_CYCLES_TO_SEC(LHS) (((double)(LHS)) * C2SEC)
#define OS_CYCLES_TO_MSEC(LHS) (((double)(LHS)) * C2MSEC)

#endif

