#include "test.h"

#define MAX_VALUE 100

void init_random_arr(int arr[], int size)
{
    printf("Pocetni niz: ");
    for (int i = 0; i < size; i++)
    {
        arr[i] = (rand() % MAX_VALUE) - MAX_VALUE/4;
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

bool compare_ints(void *elem1, void *elem2)
{
    int x = *(int*)elem1;
    int y = *(int*)elem2;

    return x < y;
}
void print_ints(void* elem)
{
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

bool compare_floats(void* elem1, void* elem2)
{
    float x = *(float*)elem1;
    float y = *(float*)elem2;

    return x < y;
}

/*
Ubacivanje elemenata sa heap_insert, uzimanje najmanjeg i brisanje najmanjeg.
*/
void test_1()
{
    printf("////////////// TEST 1 ///////////////\n\n");
    min_heap_t heap;
    init_min_heap(&heap, 10u, sizeof(int), compare_ints);

    heap_insert(&heap, &(int){5});
    heap_insert(&heap, &(int){2});
    heap_insert(&heap, &(int){7});
    heap_insert(&heap, &(int){-7});
    heap_insert(&heap, &(int){117});
    heap_insert(&heap, &(int){21});
    heap_insert(&heap, &(int){0});
    heap_insert(&heap, &(int){14});
    printf("Inicijalni heap: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    int min = *(int*)get_min(&heap);
    pop_min(&heap);
    printf("Min element: %d\n", min);

    heap_dump(&heap, print_ints);
    destroy_heap(&heap);
    printf("\n");
}

/*
Konstrukcija heap strukture od niza, brisanje elementa sa indexa 2.
*/
void test_2()
{
    printf("\n////////////// TEST 2 ///////////////\n\n");
    
    min_heap_t heap;
    init_min_heap(&heap, 20, sizeof(int), compare_ints);

    int arr[15];
    init_random_arr(arr, 15);
    build_heap(&heap, arr, 15);
    
    printf("Heap nakon brisanja elementa: ");
    heap_delete(&heap, 2);
    heap_dump(&heap, print_ints);
    printf("\n");

    destroy_heap(&heap);
}

/*
Sortiranje niza sa heap_sort.
*/
void test_3()
{
    printf("\n////////////// TEST 3 ///////////////\n\n");

    int niz[13];
    init_random_arr(niz, 13);

    heap_sort_ints(niz, 13);
    
    printf("Sortiran niz: ");
    for (int i = 0; i < 13; i++)
    {
        printf("%d,", niz[i]);
    }
    printf("\n");
}

/*
    Brisanje vise elemenata strukture.
*/
void test_4()
{
    printf("\n////////////// TEST 4 ///////////////\n\n");

    min_heap_t heap;
    int arr[15];
    init_random_arr(arr, 15);
    init_min_heap(&heap, 100, sizeof(int), compare_ints);

    build_heap(&heap, arr, 15);
    printf("Heap od datog niza: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    for (int i = 0; i < 6; i+=2)
    {
        heap_delete(&heap, i);
    }

    printf("Heap nakon brisanja svakog drugog elementa: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    destroy_heap(&heap);

}

/*
    Ubacivanje elemenata do maksimuma, i brisanje do minimuma.
*/
void test_5()
{
    printf("\n////////////// TEST 5 ///////////////\n\n");

    min_heap_t heap;
    int arr[15];
    init_random_arr(arr, 15);
    init_min_heap(&heap, 35, sizeof(int), compare_ints);

    build_heap(&heap, arr, 15);

    printf("Heap od datog niza: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    for (int i = 0; i < 1000; i++)
    {
        if (!heap_full(&heap))
        {
            heap_insert(&heap, &(int){rand() % MAX_VALUE});
        }
        else
        {
            printf("Heap popunjen!\n");
            break;
        }
    }

    printf("Heap nakon ubacenih elemenata: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    for (int i = 0; i < 1000; i++)
    {
        if (!heap_empty(&heap))
        {
            
            heap_delete(&heap, 0);
        }
        else
        {
            printf("Heap prazan!\n");
            break;
        }
    }

    printf("Heap nakon svega: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    destroy_heap(&heap);
}

void test_6()
{

}

void test_7()
{

}

void test_8()
{

}

void test_9()
{

}