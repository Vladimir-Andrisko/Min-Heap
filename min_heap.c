#include "min_heap.h"

static inline size_t get_parent(size_t index);
static inline size_t get_left(size_t index);
static inline size_t get_right(size_t index);
static inline void* get_element(const min_heap_t* heap, const size_t index);
static inline void swap_elements(void *a, void *b, size_t element_size);

static inline size_t get_parent(size_t index)
{
    return (size_t)(--index)/2U;
}

static inline size_t get_left(size_t index)
{
    return (2U*index) + 1U;
}

static inline size_t get_right(size_t index)
{
    return (2U*index) + 2U;
}

static inline void* get_element(const min_heap_t* heap, const size_t index)
{
    return (unsigned char*)heap->data + index * heap->element_size;
}

static inline void swap_elements(void *a, void *b, size_t element_size)
{
    unsigned char temp[element_size];
    
    memcpy(temp, a, element_size);
    memcpy(a, b, element_size);
    memcpy(b, temp, element_size);
}

size_t init_min_heap(min_heap_t* heap_structure, size_t size, size_t element_size, bool (*compare)(void* elem1, void* elem2))
{
    heap_structure->capacity = size;
    heap_structure->size = 0u;
    heap_structure->element_size = element_size;
    heap_structure->compare_cb = compare;

    heap_structure->data = malloc(size * element_size);

    return (heap_structure->data != nullptr);
}

void heapify_down(const min_heap_t* heap, size_t index)
{
    while (index < heap->size)
    {
        size_t left = get_left(index);
        size_t right = get_right(index);
        size_t smallest = index;

        if ((left < heap->size) && (heap->compare_cb(get_element(heap, left), get_element(heap, smallest))))
        {
            smallest = left;
        }

        if ((right < heap->size) && (heap->compare_cb(get_element(heap, right), get_element(heap, smallest))))
        {
            smallest = right;
        }

        if (smallest == index)
        {
            break;
        }

        swap_elements(get_element(heap, index), get_element(heap, smallest), heap->element_size);
        index = smallest;
    }
}

void heapify_up(const min_heap_t* heap, size_t index)
{

    while (index > 0u)
    {
        size_t parent = get_parent(index);

        if (heap->compare_cb(get_element(heap, parent), get_element(heap, index)))
        {
            break;
        }

        swap_elements(get_element(heap, parent), get_element(heap, index), heap->element_size);
        index = parent;
    }
}

void build_heap(min_heap_t* heap, const void* arr, size_t arr_size)
{
    heap->size = arr_size;
    memcpy(heap->data, arr, arr_size * heap->element_size);

    for (size_t i = (arr_size/2u) - 1u; i > 0u; i--)
    {   
        heapify_down(heap, i);
    }
    heapify_down(heap, 0u);
}

void destroy_heap(const min_heap_t* heap){
    free(heap->data);
}

void* get_min(const min_heap_t* heap){
    if(heap->size > 0u){
        return heap->data;
    }
    return nullptr;
}

void pop_min(min_heap_t* heap){
    assert(heap->size > 0);

    if (heap->size == 1)
    {
        heap->size--;
        return;
    }

    heap->size--;
    void* last_el = get_element(heap, heap->size);

    memcpy(get_element(heap, 0u), last_el, heap->element_size);
    heapify_down(heap, 0u);
}

void heap_insert(min_heap_t* heap, void* elem){
    if (heap->size >= heap->capacity)
    {
        return;
    }

    if (heap->size == 0u)
    {
        memcpy(get_element(heap, 0u), elem, heap->element_size);    
        heap->size++;
        return;
    }

    size_t i = heap->size++;
    memcpy(get_element(heap, i), elem, heap->element_size);
    heapify_up(heap, i);
}

void heap_delete(min_heap_t* heap, size_t index)
{   
    heap->size--;
    memcpy(get_element(heap, index), get_element(heap, heap->size), heap->element_size);

    if ((index > 0u) && (heap->compare_cb(get_element(heap, index), get_element(heap, get_parent(index)))))
    {
        heapify_up(heap, index);
    }
    else
    {
        heapify_down(heap, index);
    }
}

void heap_dump(const min_heap_t* heap, void (*print_cb)(void* elem))
{
    size_t index = 0u;
    while (index < heap->size)
    {
        print_cb(get_element(heap, index));
        ++index;
    }
}

void heap_sort(min_heap_t* heap)
{
    size_t temp = heap->size;
    for (int i = heap->size-1; i >= 1; i--)
    {
        swap_elements(get_element(heap, 0u), get_element(heap, i), heap->element_size);
        heap->size--;
        heapify_down(heap, 0u);
    }
    heap->size = temp;
}

bool heap_empty(min_heap_t* heap)
{
    return (heap->size == 0);
}
