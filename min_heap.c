#include "min_heap.h"

#define COMPARE gas

static inline size_t get_parent(size_t index)
{
    return (size_t)((index-1)/2.0);
}

static inline size_t get_left(size_t index)
{
    return 2*index + 1;
}

static inline size_t get_right(size_t index)
{
    return 2*index + 2;
}

static inline void* get_element(min_heap_t* heap, size_t index)
{
    return (unsigned char*)(heap->data + index * heap->element_size);
}

static void swap_elements(void *a, void *b, size_t element_size)
{
    unsigned char temp[element_size];

    memcpy(temp, a, element_size);
    memcpy(a, b, element_size);
    memcpy(b, temp, element_size);
}

size_t init_min_heap(min_heap_t* heap_structure, size_t size, size_t element_size, int (*compare)(void*, void*))
{
    heap_structure->capacity = size;
    heap_structure->size = 0;
    heap_structure->element_size = element_size;
    heap_structure->compare_cb = compare;

    heap_structure->data = malloc(size * element_size);

    return (heap_structure->data == nullptr);
}

void heapify(min_heap_t* heap, size_t index)
{
    size_t left = get_left(index);
    size_t right = get_right(index);
    size_t smallest;

    if (left < heap->size && heap->compare_cb(get_element(heap, left), get_element(heap, index)))
    {
        smallest = left;
    }else
    {
        smallest = index;
    }

    if (right < heap->size && heap->compare_cb(get_element(heap, right), get_element(heap, smallest)))
    {
        smallest = right;
    }

    if (smallest != index)
    {
        swap_elements(get_element(heap, index), get_element(heap, smallest), heap->element_size);
        heapify(heap, smallest);
    }

}

void build_heap(min_heap_t* array, size_t size){
    for (int i = size/2; i > 0; i--){
        heapify(array, i);
    }
}

void destroy_heap(min_heap_t* heap){
    free(heap->data);
}

void* get_min(min_heap_t* heap){
    if(heap->size > 0){
        return heap->data;
    }
    return nullptr;
}

void pop_min(min_heap_t* heap){
    heap->size--;
    void* last_el = get_element(heap, heap->size);

    memcpy(get_element(heap, 0), last_el, heap->element_size);
    heapify(heap, 0);
}

void heap_insert(min_heap_t* heap, void* elem){
    if (heap->size == 0)
    {
        memcpy(get_element(heap, 0), elem, heap->element_size);    
        heap->size++;
        return;
    }

    size_t i = heap->size;
    heap->size++;
    memcpy(get_element(heap, i), elem, heap->element_size);

    size_t parent = get_parent(i);
    while (i > 0 && heap->compare_cb(get_element(heap, i), get_element(heap, parent)))
    {
        swap_elements(get_element(heap, i), get_element(heap, parent), heap->element_size);
        i = parent;
        parent = get_parent(i);
    }

}

void heap_dump(min_heap_t* heap){
    size_t index = 0;
    while (index < heap->size)
    {
        printf("%d, ", *(int*)get_element(heap, index));
        index++;
    }
    printf("\n");
}
