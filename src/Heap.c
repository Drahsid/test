#include "Heap.h"
#include <string.h>

Heap* gpHeap;

void Heap_Construct(Heap* heap, void* start, SIZE_TYPE size) {
    Heap_Block* block;

    // set up basic info
    heap->start = (SIZE_TYPE)start + sizeof(Heap);
    heap->size = size - sizeof(Heap);

    // set up for first block
    block = (Heap_Block*)HEAP_ALIGN(heap->start);
    size -= ((SIZE_TYPE)block) - ((SIZE_TYPE)start);
    size = HEAP_ALIGN(size);

    block->free_last = NULL;
    block->free_next = NULL;
    block->used_last = NULL;
    block->used_next = NULL;

    block->used = HEAP_BLOCK_HEADER_SIZE;
    block->free = size - HEAP_BLOCK_HEADER_SIZE;

    heap->used_head = block;

    if (block->free) heap->free_head = block;
    else heap->free_head = NULL;
}

void* Heap_Alloc(Heap* heap, SIZE_TYPE size) {
    Heap_Block* block;
    Heap_Block* new_block;

    size = HEAP_ALIGN(size) + HEAP_BLOCK_HEADER_SIZE;
    block = heap->free_head;

    while (block) {
        // does block have space?
        if (block->free >= size) {
            new_block = (Heap_Block*)(((SIZE_TYPE)block) + block->used);

            new_block->used = size;
            new_block->free = block->free - size;

            if (new_block->free) {
                new_block->free_last = block;
                new_block->free_next = block->free_next;

                if (block->free_next) new_block->free_next->free_last = new_block;
                block->free_next = new_block;

                if (heap->free_tail == block) heap->free_tail = new_block;
            }
            else {
                new_block->free_next = NULL;
                new_block->free_last = NULL;
            }

            block->free = 0;

            if (block->free_last) block->free_last->free_next = block->free_next;
            if (block->free_next) block->free_next->free_last = block->free_last;

            if (heap->free_head == block) heap->free_head = block->free_next;
            if (heap->free_tail == block) {
                if (block->free_next) heap->free_tail = block->free_next;
                else heap->free_tail = block->free_last;
            }

            block->free_last = NULL;
            block->free_next = NULL;

            new_block->used_last = block;
            new_block->used_next = block->used_next;

            if (block->used_next) new_block->used_next->used_last = new_block;
            block->used_next = new_block;

            return (void*)(((SIZE_TYPE)new_block) + HEAP_BLOCK_HEADER_SIZE);
        }

        block = block->free_next;
    }

    return NULL;
}

void* Heap_Alloc_Tail(Heap* heap, SIZE_TYPE size) {
    Heap_Block* block;
    Heap_Block* new_block;

    size = HEAP_ALIGN(size) + HEAP_BLOCK_HEADER_SIZE;
    block = heap->free_tail;

    while (block) {
        // does block have space?
        if (block->free >= size) {
            new_block = (Heap_Block*)(((SIZE_TYPE)block) + block->used);

            new_block->used = size;
            new_block->free = block->free - size;

            if (new_block->free) {
                new_block->free_last = block;
                new_block->free_next = block->free_next;

                if (block->free_next) new_block->free_next->free_last = new_block;
                block->free_next = new_block;

                if (heap->free_tail == block) heap->free_tail = new_block;
            }
            else {
                new_block->free_next = NULL;
                new_block->free_last = NULL;
            }

            block->free = 0;

            if (block->free_last) block->free_last->free_next = block->free_next;
            if (block->free_next) block->free_next->free_last = block->free_last;

            if (heap->free_head == block) heap->free_head = block->free_next;
            if (heap->free_tail == block) {
                if (block->free_next) heap->free_tail = block->free_next;
                else heap->free_tail = block->free_last;
            }

            block->free_last = NULL;
            block->free_next = NULL;

            new_block->used_last = block;
            new_block->used_next = block->used_next;

            if (block->used_next) new_block->used_next->used_last = new_block;
            block->used_next = new_block;

            return (void*)(((SIZE_TYPE)new_block) + HEAP_BLOCK_HEADER_SIZE);
        }

        block = block->free_last;
    }

    return NULL;
}

void Heap_Free(Heap* heap, void* address) {
    Heap_Block* block;
    Heap_Block* free_last;
    Heap_Block* used_last;

    block = (Heap_Block*)(((SIZE_TYPE)address) - HEAP_BLOCK_HEADER_SIZE);
    used_last = block->used_last;

    if (!used_last->free) {

        // find previous free block
        if (block->free_last) free_last = block->free_last;
        else {
            free_last = block->used_last;
            while (free_last) {
                if (free_last->free) break;
                free_last = free_last->used_last;
            }
        }

        // choose where to add to the free list
        if (free_last) {
            used_last->free_last = free_last;
            used_last->free_next = free_last->free_next;

            if (free_last->free_next) used_last->free_next->free_last = used_last;

            free_last->free_next = used_last;

            if (heap->free_tail == free_last) heap->free_tail = used_last;
        }
        else {
            used_last->free_next = heap->free_head;

            if (heap->free_head) heap->free_head->free_last = used_last;
            else heap->free_tail = used_last;
            heap->free_head = used_last;
        }
    }

    used_last->free += block->used + block->free;

    if (block->used_next) block->used_next->used_last = block->used_last;
    block->used_last->used_next = block->used_next;

    if (block->free) {
        if (block->free_last) block->free_last->free_next = block->free_next;
        if (block->free_next) block->free_next->free_last = block->free_last;

        if (heap->free_tail == block) heap->free_tail = block->free_last;
    }
}

void* Heap_Realloc(Heap* heap, void* address, SIZE_TYPE size) {
    Heap_Block* block;
    Heap_Block* new_block;

    size = HEAP_ALIGN(size + HEAP_BLOCK_HEADER_SIZE);
    block = (Heap_Block*)(((SIZE_TYPE)address) - HEAP_BLOCK_HEADER_SIZE);

    if (size <= block->used || block->free >= size - block->used) {
        return (void*)(((SIZE_TYPE)block) + HEAP_BLOCK_HEADER_SIZE);
    }
    else {
        new_block = (Heap_Block*)Heap_Alloc(heap, size - HEAP_BLOCK_HEADER_SIZE);
        memcpy(new_block, address, block->used);
        Heap_Free(heap, address);
        return new_block;
    }

    return 0;
}

void Heap_Wipe(Heap* heap) {
    while (heap->used_head->used_next) {
        Heap_Free(heap, (void*)(((SIZE_TYPE)heap->used_head->used_next) + HEAP_BLOCK_HEADER_SIZE));
    }
}

SIZE_TYPE Heap_Get_Free(Heap* heap) {
    SIZE_TYPE total = 0;
    Heap_Block* block;

    block = heap->free_head;
    while(block) {
        total += block->free;
        block = block->free_next;
    }

    return total;
}

Heap_Block* Heap_Get_Largest_Free(Heap* heap) {
    SIZE_TYPE largest = 0;
    Heap_Block* block;
    Heap_Block* largest_block;

    while (block)
    {
        if (block->free >= largest) {
            largest = block->free;
            largest_block = block;
        }


        block = block->free_next;
    }

    return largest_block;
}

void* malloc(SIZE_TYPE size) {
    return Heap_Alloc(gpHeap, size);
}

void* malloc_tail(SIZE_TYPE size) {
    return Heap_Alloc_Tail(gpHeap, size);
}

void free(SIZE_TYPE address) {
    Heap_Free(gpHeap, address);
}

void* realloc(SIZE_TYPE address, SIZE_TYPE size) {
    return Heap_Realloc(gpHeap, address, size);
}

