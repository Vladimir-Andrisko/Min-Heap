#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#pragma CHECK_MISRA("-13.5")    /*Expressions in for loop should be used only for loop cotrol. Ignored beacuse it is heavy on performance*/


typedef struct min_heap{
    size_t size;
    size_t capacity;
    size_t element_size;
    bool (*compare_cb)(void* elem1, void* elem2);
    void* data;
} min_heap_t;

size_t init_min_heap(min_heap_t* heap_structure, size_t size, size_t element_size, bool (*compare)(void* elem1, void* elem2));

void build_heap(min_heap_t* heap, const void* arr, size_t arr_size);
void destroy_heap(const min_heap_t* heap);

void heap_insert(min_heap_t* heap, const void* elem);
void heap_delete(min_heap_t* heap, size_t index);

void* get_min(const min_heap_t* heap);
void pop_min(min_heap_t* heap);

void heap_dump(const min_heap_t* heap, void (*print_cb)(void* elem));
void heap_sort(const min_heap_t* heap, void* arr);

bool heap_empty(const min_heap_t* heap);
bool heap_full(const min_heap_t* heap);
void clear_heap(min_heap_t* heap);

#endif
