#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

// #pragma CHECK_MISRA("none")
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
// #pragma CHECK_MISRA("all")
// #pragma CHECK_MISRA("-5.6")
// #pragma CHECK_MISRA("-5.7")
// #pragma CHECK_MISRA("-20.4")
// #pragma CHECK_MISRA("-17.4")
// #pragma CHECK_MISRA("-12.2")
// #pragma CHECK_MISRA("-12.4")
// #pragma CHECK_MISRA("-12.13")
// #pragma CHECK_MISRA("-13.5")

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

void heap_insert(min_heap_t* heap, void* elem);
void heap_delete(min_heap_t* heap, size_t index);

void* get_min(const min_heap_t* heap);
void pop_min(min_heap_t* heap);

void heap_dump(const min_heap_t* heap, void (*print_cb)(void* elem));
void heap_sort(min_heap_t* heap);

bool heap_empty(min_heap_t* heap);
bool heap_full(min_heap_t* heap);
void clear_heap(min_heap_t* heap);

#endif
