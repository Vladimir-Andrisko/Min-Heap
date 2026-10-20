#include "min_heap.h"

static inline size_t get_parent(size_t index);
static inline size_t get_left(size_t index);
static inline size_t get_right(size_t index);
static inline void* get_element(const min_heap_t* heap, const size_t index);
static inline void swap(void *a, void *b, size_t element_size);
static void heapify_down(const min_heap_t* heap, size_t index);
static void heapify_up(const min_heap_t* heap, size_t index);

static inline size_t get_parent(size_t index)
{
    return (index - 1U)/2U;
}

static inline size_t get_left(size_t index)
{
    return (2U * index) + 1U;
}

static inline size_t get_right(size_t index)
{
    return (2U * index) + 2U;
}

static inline void* get_element(const min_heap_t* heap, const size_t index)
{
    return (unsigned char*)heap->data + (index * heap->element_size);
}

static inline void swap(void *a, void *b, const size_t element_size)
{
    unsigned char* x = (unsigned char*)a;
    unsigned char* y = (unsigned char*)b;
    unsigned char temp;
    
    for (size_t i = 0; i < element_size; i++)
    {
        temp = x[i];
        x[i] = y[i];
        y[i] = temp;
    }
}

size_t init_min_heap(min_heap_t* heap_structure, size_t size, size_t element_size, bool (*compare)(void* elem1, void* elem2))
{
    heap_structure->capacity = size;
    heap_structure->size = 0u;
    heap_structure->element_size = element_size;
    heap_structure->compare_cb = compare;

    /* 
    malloc() nije garantovan u freestanding C23 okruzenjima.
    Koristi se iskljucivo pri inicijalizaciji heap-a, kako bi se
    izbegla dinamicka alokacija tokom RT operacija. 
    */
    heap_structure->data = malloc(size * element_size);

    return (heap_structure->data != nullptr);
}

static void heapify_down(const min_heap_t* heap, size_t index)
{
    size_t size = heap->size;

    while (index < (size / 2u))
    {
        size_t left = get_left(index);
        size_t right = get_right(index);
        size_t smallest = index;


        void* left_elem = get_element(heap, left);
        void* smallest_elem = get_element(heap, smallest);

        if (heap->compare_cb(left_elem, smallest_elem))
        {
            smallest = left;
            smallest_elem = left_elem;
        }

        if (right < size)
        {
            void* right_elem = get_element(heap, right);

            if (heap->compare_cb(right_elem, smallest_elem))
            {
                smallest = right;
                smallest_elem = right_elem;
            }
        }

        if (smallest == index)
        {
            break;
        }

        void* index_elem = get_element(heap, index);
        swap(index_elem, smallest_elem, heap->element_size);
        index = smallest;
    }
}

static void heapify_up(const min_heap_t* heap, size_t index)
{
    while (index > 0u)
    {
        size_t parent = get_parent(index);
        void* parent_elem = get_element(heap, parent);
        void* index_elem = get_element(heap, index);

        if (heap->compare_cb(parent_elem, index_elem))
        {
            break;
        }

        swap(parent_elem, index_elem, heap->element_size);
        index = parent;
    }
}

void build_heap(min_heap_t* heap, const void* arr, const size_t arr_size)
{
    /* 
    assert() nije garantovan u freestanding C23 okruzenjima.
    Koristi se za detekciju neispravnih argumenata i krsenja
    preduslova funkcije tokom izvrsavanja programa. 
    */
    assert(arr_size > 0u);
    assert(heap->capacity >= arr_size);

    heap->size = arr_size;
    memmove(heap->data, arr, arr_size * heap->element_size);

    size_t index = arr_size / 2u;
    while (index > 0u)
    {   
        --index;
        heapify_down(heap, index);
    }
}

void destroy_heap(const min_heap_t* heap){
    free(heap->data);
}

void* get_min(const min_heap_t* heap){
    void* ret_value;
    if(heap->size > 0u){
        ret_value = heap->data;
    }
    else
    {
        ret_value = nullptr;
    }

    return ret_value;
}

void pop_min(min_heap_t* heap){
    /* 
    assert() nije garantovan u freestanding C23 okruzenjima.
    Koristi se za detekciju neispravnih argumenata i krsenja
    preduslova funkcije tokom izvrsavanja programa. 
    */

    assert(heap->size > 0u);

    heap->size--;
    if (heap->size > 0u)
    {   
        void* last_el = get_element(heap, heap->size);

        memmove(get_element(heap, 0u), last_el, heap->element_size);
        heapify_down(heap, 0u);
    } 
}

void heap_insert(min_heap_t* heap, const void* elem){
    /* 
    assert() nije garantovan u freestanding C23 okruzenjima.
    Koristi se za detekciju neispravnih argumenata i krsenja
    preduslova funkcije tokom izvrsavanja programa. 
    */
    assert(heap->size < heap->capacity);

    if (heap->size == 0u)
    {
        memmove(get_element(heap, 0u), elem, heap->element_size);    
        heap->size++;
    }
    else
    {
        size_t i = heap->size;
        heap->size++;
        memmove(get_element(heap, i), elem, heap->element_size);
        heapify_up(heap, i);
    }
}

void heap_delete(min_heap_t* heap, size_t index)
{  
    /* 
    assert() nije garantovan u freestanding C23 okruzenjima.
    Koristi se za detekciju neispravnih argumenata i krsenja
    preduslova funkcije tokom izvrsavanja programa. 
    */
    assert(index < heap->size);

    heap->size--;
    if (index < heap->size)
    {
        void* index_element = get_element(heap, index);
        void* last_element = get_element(heap, heap->size);

        memmove(index_element, last_element, heap->element_size);

        if (index == 0u)
        {
            heapify_down(heap, index);
        }
        else
        {
            size_t parent = get_parent(index);
            void* parent_element = get_element(heap, parent);

            if (heap->compare_cb(index_element, parent_element))
            {
                heapify_up(heap, index);
            }
            else
            {
                heapify_down(heap, index);
            }
        }
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

void heap_sort(const min_heap_t* heap, void* arr)
{
    min_heap_t temp_heap = *heap;
    temp_heap.data = arr;

    if (temp_heap.size > 0u)
    {
        memmove(temp_heap.data, heap->data, temp_heap.size * temp_heap.element_size);
    }

    while (temp_heap.size > 1u)
    {
        size_t last_index = temp_heap.size - 1u;

        void* first_element = temp_heap.data;
        void* last_element = get_element(&temp_heap, last_index);

        swap(first_element, last_element, temp_heap.element_size);

        temp_heap.size--;
        heapify_down(&temp_heap, 0u);
    }
}

bool heap_empty(const min_heap_t* heap)
{
    return (bool)(heap->size == 0u);
}

bool heap_full(const min_heap_t* heap)
{
    return (bool)(heap->size == heap->capacity);
}

void clear_heap(min_heap_t* heap)
{
    heap->size = 0u;
}
