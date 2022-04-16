#ifndef HEAP_H
#define HEAP_H

#include "common.h"

#define HEAP_BLOCK_ALIGNMENT (16)
#define HEAP_ALIGN(lhs) ((((SIZE_TYPE)lhs) + HEAP_BLOCK_ALIGNMENT - 1) & ~(HEAP_BLOCK_ALIGNMENT - 1))
#define HEAP_BLOCK_HEADER_SIZE (HEAP_ALIGN(sizeof(Heap_Block)))
#define HEAP_END(lhs) (((Heap*)lhs)->start + lhs->size)

typedef struct Heap_Block_s {
    struct Heap_Block_s* free_last;
    struct Heap_Block_s* free_next;
    struct Heap_Block_s* used_last;
    struct Heap_Block_s* used_next;
    SIZE_TYPE used, free;
} Heap_Block;

typedef struct {
    Heap_Block* free_head;
    Heap_Block* free_tail;
    Heap_Block* used_head;
    SIZE_TYPE start;
    SIZE_TYPE size;
} Heap;

extern void Heap_Construct(Heap* heap, void* start, SIZE_TYPE size);
extern void* Heap_Alloc_Tail(Heap* heap, SIZE_TYPE size);
extern void Heap_Free(Heap* heap, void* address);
extern void* Heap_Realloc(Heap* heap, void* address, SIZE_TYPE size);
extern void Heap_Wipe(Heap* heap);
extern Heap_Block* Heap_Get_Largest_Free(Heap* heap);
extern void* malloc(SIZE_TYPE size);
extern void* malloc_tail(SIZE_TYPE size);
extern void free(SIZE_TYPE address);
extern void* realloc(SIZE_TYPE address, SIZE_TYPE size);

extern Heap* gpHeap;

#endif

