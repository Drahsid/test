#ifndef LIBC_H
#define LIBC_H

#include "common.h"

extern void memset_u8(u8* dest, u8 value, SIZE_TYPE length);
extern void memset_u16(u16* dest, u16 value, SIZE_TYPE length);
extern void memset_u32(u32* dest, u32 value, SIZE_TYPE length);
extern void memset_u64(u64* dest, u64 value, SIZE_TYPE length);

#endif

