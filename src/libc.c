#include "libc.h"

void memset_u8(u8* dest, u8 value, SIZE_TYPE length) {
    while (length -= sizeof(value)) {
        *dest = value;
        dest++;
    }
}

void memset_u16(u16* dest, u16 value, SIZE_TYPE length) {
    while (length -= sizeof(value)) {
        *dest = value;
        dest++;
    }
}

void memset_u32(u32* dest, u32 value, SIZE_TYPE length) {
    while (length -= sizeof(value)) {
        *dest = value;
        dest++;
    }
}

void memset_u64(u64* dest, u64 value, SIZE_TYPE length) {
    while (length -= sizeof(value)) {
        *dest = value;
        dest++;
    }
}

void __assert_func() {}
void __assert() {}
