#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct min_heap{
    size_t size;
    size_t capacity;
    size_t element_size;
    int (*compare_cb)(void*, void*);
    void* data;
} min_heap_t;

size_t init_min_heap(min_heap_t* heap_structure, size_t size, size_t element_size, int (*compare)(void*, void*));
void heapify(min_heap_t* array, size_t index);
void build_heap(min_heap_t* array, size_t size);
void destroy_heap(min_heap_t* heap);
void heap_insert(min_heap_t* heap, void* elem);
void heap_dump(min_heap_t* heap);
void* get_min(min_heap_t* heap);
void pop_min(min_heap_t* heap);

#endif