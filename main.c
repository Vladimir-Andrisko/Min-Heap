#include "min_heap.h"

int compare_ints(void *a, void *b){
    int x = *(int*)a;
    int y = *(int*)b;

    return x <= y;
}

int main()
{   
    min_heap_t heap;
    init_min_heap(&heap, 10, sizeof(int), compare_ints);
    int el1 = 5;
    int el2 = 2;
    int el3 = 7;
    int el4 = 14;
    int el5 = 11;
    heap_insert(&heap, (void*)&el1);
    heap_insert(&heap, (void*)&el2);
    heap_insert(&heap, (void*)&el3);
    heap_insert(&heap, (void*)&el4);
    heap_insert(&heap, (void*)&el5);


    int min = *(int*)get_min(&heap);
    pop_min(&heap);
    printf("MINIMALNA KURCINA: %d\n", min);
    heap_dump(&heap);
    destroy_heap(&heap);
    return 0;
}