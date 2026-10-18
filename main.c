#include "min_heap.h"
#include <stdio.h>

bool compare_ints(void *elem1, void *elem2){
    int x = *(int*)elem1;
    int y = *(int*)elem2;

    return x <= y;
}

void print_ints(void* elem){
    printf("%d,", *(int*)elem);
}

void heap_sort_ints(int arr[], size_t arr_size)
{
    min_heap_t temp;
    init_min_heap(&temp, arr_size, sizeof(int), compare_ints);

    build_heap(&temp, arr, arr_size);
    heap_sort(&temp);
    memcpy(arr, temp.data, arr_size * sizeof(int));
}

int main()
{   
    {
        printf("////////////// TEST 1 ///////////////\n\n");
        min_heap_t heap;
        init_min_heap(&heap, 10, sizeof(int), compare_ints);

        heap_insert(&heap, &(int){5});
        heap_insert(&heap, &(int){2});
        heap_insert(&heap, &(int){7});
        heap_insert(&heap, &(int){-7});
        heap_insert(&heap, &(int){117});
        heap_insert(&heap, &(int){21});
        heap_insert(&heap, &(int){0});
        heap_insert(&heap, &(int){14});

        int min = *(int*)get_min(&heap);
        pop_min(&heap);
        printf("MINIMALNI: %d\n", min);
        heap_dump(&heap, print_ints);
        destroy_heap(&heap);
    }

    {
        printf("\n////////////// TEST 2 ///////////////\n\n");
    
        min_heap_t heap;
        init_min_heap(&heap, 20, sizeof(int), compare_ints);

        int niz[13] = {13, -1, -17, 5, 4, 2, 1, 123, 54, 47, 11, 67, 69};
        
        build_heap(&heap, niz, 13);
        heap_dump(&heap, print_ints);
        printf("\n");
        heap_delete(&heap, 2);
        
        heap_dump(&heap, print_ints);
        printf("\n");
    }

    {
        printf("\n////////////// TEST 3 ///////////////\n\n");
    
        min_heap_t heap;


        int niz[13] = {13, -1, -17, 5, 4, 2, 1, 123, 54, 47, 11, 67, 69};
        heap_sort_ints(niz, 13);
        
        for(int i = 0; i < 13; i++){
            printf("%d,", niz[i]);
        }
        printf("\n");
    }

    return 0;
}
