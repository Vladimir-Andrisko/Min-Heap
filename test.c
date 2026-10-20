#include "test.h"

#define MAX_VALUE 100

/* Ints */
void init_random_arr(int32_t arr[], int32_t size)
{
    printf("Pocetni niz: ");
    for (int32_t i = 0; i < size; i++)
    {
        arr[i] = (rand() % MAX_VALUE) - MAX_VALUE/4;
        printf("[%"PRId32"] ", arr[i]);
    }
    printf("\n");
}

bool compare_ints(void *elem1, void *elem2)
{
    int32_t x = *(int32_t*)elem1;
    int32_t y = *(int32_t*)elem2;

    return x < y;
}

void print_ints(void* elem)
{
    printf("[%"PRId32"] ", *(int32_t*)elem);
}

void heap_sort_ints(int32_t arr[], size_t arr_size)
{
    min_heap_t temp;
    init_min_heap(&temp, arr_size, sizeof(int32_t), compare_ints);
    build_heap(&temp, arr, arr_size);

    heap_sort(&temp, arr);
    destroy_heap(&temp);
}

/* Floats */
bool compare_floats(void* elem1, void* elem2)
{
    float x = *(float*)elem1;
    float y = *(float*)elem2;

    return x < y;
}

void print_floats(void* elem)
{
    printf("[%.2f] ", *(float*)elem);
}

/* Example struct */
typedef struct a_star_node{
    int_least16_t id;
    double f_cost;
    double h_cost;
    double g_cost;
} a_star_node_t;

bool compare_a_star(void* elem1, void* elem2)
{
    a_star_node_t x = *(a_star_node_t*)elem1;
    a_star_node_t y = *(a_star_node_t*)elem2;

    bool ret_val = false;

    if (x.f_cost == y.f_cost)
    {
        ret_val = x.h_cost < y.h_cost;
    }
    else
    {
        ret_val = x.f_cost < y.f_cost;
    }

    return ret_val;
}

void print_a_star(void* elem)
{
    a_star_node_t x = *(a_star_node_t*)elem;
    printf("[Node id: %"PRIdLEAST16", f: %.2lf, h: %.2lf] ", x.id, x.f_cost, x.h_cost);
}

/*
Ubacivanje elemenata sa heap_insert, uzimanje najmanjeg i brisanje najmanjeg.
*/
void test_1(void)
{
    printf("////////////// TEST 1 ///////////////\n\n");
    min_heap_t heap;
    init_min_heap(&heap, 10u, sizeof(int32_t), compare_ints);

    heap_insert(&heap, &(int32_t){5});
    heap_insert(&heap, &(int32_t){2});
    heap_insert(&heap, &(int32_t){7});
    heap_insert(&heap, &(int32_t){-7});
    heap_insert(&heap, &(int32_t){117});
    heap_insert(&heap, &(int32_t){21});
    heap_insert(&heap, &(int32_t){0});
    heap_insert(&heap, &(int32_t){14});
    printf("Inicijalni heap: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    int32_t min = *(int32_t*)get_min(&heap);
    pop_min(&heap);
    printf("Min element: %"PRId32"\n", min);

    printf("Heap posle brisanja min elementa: ");
    heap_dump(&heap, print_ints);
    destroy_heap(&heap);
    printf("\n");
}

/*
    Testiranje int32_t sa dupliranim elementima.
    Brisanje poslednjeg elementa i vadjenje svih elemenata po redu.
*/
void test_2(void)
{
    printf("\n////////////// TEST 2 ///////////////\n\n");

    min_heap_t heap;
    int32_t arr[8u] = {-4, 7, 7, 0, 20, -4, 3, 12};

    init_min_heap(&heap, 10u, sizeof(int32_t), compare_ints);
    build_heap(&heap, arr, 8u);

    printf("Inicijalni heap: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    heap_delete(&heap, heap.size - 1u);

    printf("Heap nakon brisanja poslednjeg elementa: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    heap_insert(&heap, &(int32_t){-12});

    printf("Heap nakon ubacivanja elementa: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    printf("Vadjenje elemenata po redu: ");
    while (!heap_empty(&heap))
    {
        print_ints(get_min(&heap));
        pop_min(&heap);
    }
    printf("\n");

    destroy_heap(&heap);
}

/*
Sortiranje niza sa heap_sort.
*/
void test_3(void)
{
    printf("\n////////////// TEST 3 ///////////////\n\n");

    int32_t niz[13];
    init_random_arr(niz, 13);

    heap_sort_ints(niz, 13);
    
    printf("Sortiran niz: ");
    for (int32_t i = 0; i < 13; i++)
    {
        printf("[%"PRId32"] ", niz[i]);
    }
    printf("\n");
}


/*
Lose inicijalizovan heap.
Struktura je namerno napisana da izazove poravnanje, a u ovom primeru korisnik pogresno pretpostavi velicinu strukture.
*/
void test_4(void)
{
    printf("\n////////////// TEST 4 ///////////////\n\n");

    min_heap_t heap;
    a_star_node_t arr[6u] = 
    {
        {1, 6.0, 3.0, 3.0}, {2, 4.0, 2.0, 2.0}, {3, 4.0, 1.0, 3.0},
        {4, 9.0, 5.0, 4.0}, {5, 4.0, 3.0, 1.0}, {6, 1.0, 0.5, 0.5}
    };

    printf("Ispis a_star elemenata: ");
    for (size_t i = 0u; i < 6u; i++)
    {
        print_a_star(&arr[i]);
    }
    printf("\n");

    init_min_heap(&heap, 10u, 26u, compare_a_star);
    build_heap(&heap, arr, 6u);

    printf("Ispis lose inicijalizovane heap strukture: ");
    heap_dump(&heap, print_a_star);
    printf("\n");

    destroy_heap(&heap);
}

/*
    Ubacivanje elemenata do maksimuma, i brisanje do minimuma.
*/
void test_5(void)
{
    printf("\n////////////// TEST 5 ///////////////\n\n");

    min_heap_t heap;
    int32_t arr[15];
    init_random_arr(arr, 15);
    init_min_heap(&heap, 35, sizeof(int32_t), compare_ints);

    build_heap(&heap, arr, 15);

    printf("Heap od datog niza: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    for (int32_t i = 0; i < 1000; i++)
    {
        if (!heap_full(&heap))
        {
            heap_insert(&heap, &(int32_t){rand() % MAX_VALUE});
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

    for (int32_t i = 0; i < 1000; i++)
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

/*
Pogresno prosledjene callback funkcije.
*/
void test_6(void)
{
    printf("////////////// TEST 6 ///////////////\n\n");
    min_heap_t heap;
    int32_t arr[8u] = {-4, 7, 7, 0, 20, -4, 3, 12};
    init_min_heap(&heap, 10u, sizeof(int32_t), compare_floats);
    build_heap(&heap, arr, 8u);
    
    printf("Heap sa pogresnom compare funkcijom: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    int32_t min = *(int32_t*)get_min(&heap);
    pop_min(&heap);
    printf("Min element: %"PRId32"\n", min);

    printf("Heap ispisan sa print_floast: ");
    heap_dump(&heap, print_floats);
    destroy_heap(&heap);
    printf("\n");
}

/*
Testiranje heap strukture sa float tipom.
Ubacivanje elemenata, uzimanje minimuma i brisanje elemenata.
*/
void test_7(void)
{
    printf("\n////////////// TEST 7 ///////////////\n\n");

    min_heap_t heap;
    init_min_heap(&heap, 10u, sizeof(float), compare_floats);

    heap_insert(&heap, &(float){3.5f});
    heap_insert(&heap, &(float){-2.75f});
    heap_insert(&heap, &(float){7.25f});
    heap_insert(&heap, &(float){0.0f});
    heap_insert(&heap, &(float){1.125f});
    heap_insert(&heap, &(float){-9.5f});
    heap_insert(&heap, &(float){3.5f});

    printf("Inicijalni heap: ");
    heap_dump(&heap, print_floats);
    printf("\n");

    float min = *(float*)get_min(&heap);
    printf("Minimalni element: %f\n", min);

    pop_min(&heap);

    printf("Heap nakon brisanja minimuma: ");
    heap_dump(&heap, print_floats);
    printf("\n");

    heap_delete(&heap, 2u);

    printf("Heap nakon brisanja elementa sa indexa 2: ");
    heap_dump(&heap, print_floats);
    printf("\n");

    destroy_heap(&heap);
}

/*
    Testiranje heap strukture sa A* cvorovima.
    Poredjenje po f_cost i h_cost, ubacivanje i brisanje cvorova.
*/
void test_8(void)
{
    printf("\n////////////// TEST 8 ///////////////\n\n");

    min_heap_t heap;

    a_star_node_t arr[6] = 
    {
        {1, 6.0, 3.0, 3.0}, {2, 4.0, 2.0, 2.0}, {3, 4.0, 1.0, 3.0},
        {4, 9.0, 5.0, 4.0}, {5, 4.0, 3.0, 1.0}, {6, 1.0, 0.5, 0.5}
    };

    init_min_heap(&heap, 10u, sizeof(a_star_node_t), compare_a_star);
    build_heap(&heap, arr, 6u);

    printf("Inicijalni heap: ");
    heap_dump(&heap, print_a_star);
    printf("\n");

    printf("Minimalni cvor: ");
    print_a_star(get_min(&heap));
    printf("\n");

    heap_delete(&heap, 3u);

    a_star_node_t new_node = {7, 2.0, 1.0, 1.0};
    heap_insert(&heap, &new_node);

    printf("Heap nakon brisanja i ubacivanja: ");
    heap_dump(&heap, print_a_star);
    printf("\n");

    printf("Vadjenje cvorova po prioritetu:\n");
    while (!heap_empty(&heap))
    {
        print_a_star(get_min(&heap));
        printf("\n");
        pop_min(&heap);
    }

    destroy_heap(&heap);
}

/*
Sortiranje float niza i niza A* cvorova.
Provera da originalna heap struktura ostaje nepromenjena.
*/
void test_9(void)
{
    printf("\n////////////// TEST 9 ///////////////\n\n");

    min_heap_t float_heap;

    float arr[7] = {2.75f, -4.5f, 3.125f, 0.0f, 2.75f, -1.0f, 5.25f};
    float sorted_arr[7];

    init_min_heap(&float_heap, 7u, sizeof(float), compare_floats);
    build_heap(&float_heap, arr, 7u);

    printf("Inicijalni float heap: ");
    heap_dump(&float_heap, print_floats);
    printf("\n");

    heap_sort(&float_heap, sorted_arr);

    printf("Sortiran float niz: ");
    for (size_t i = 0u; i < 7u; i++)
    {
        print_floats(&sorted_arr[i]);
    }
    printf("\n");

    printf("Float heap nakon sortiranja: ");
    heap_dump(&float_heap, print_floats);
    printf("\n");

    destroy_heap(&float_heap);


    min_heap_t a_star_heap;

    a_star_node_t nodes[5] = {
        {1, 8.0, 4.0, 4.0},
        {2, 3.0, 2.0, 1.0},
        {3, 3.0, 1.0, 2.0},
        {4, 10.0, 7.0, 3.0},
        {5, 1.0, 0.5, 0.5}
    };

    a_star_node_t sorted_nodes[5];

    init_min_heap(&a_star_heap, 5u, sizeof(a_star_node_t), compare_a_star);
    build_heap(&a_star_heap, nodes, 5u);

    printf("\nInicijalni A* heap: ");
    heap_dump(&a_star_heap, print_a_star);
    printf("\n");

    heap_sort(&a_star_heap, sorted_nodes);

    printf("Sortirani A* cvorovi:\n");
    for (size_t i = 0u; i < 5u; i++)
    {
        print_a_star(&sorted_nodes[i]);
        printf("\n");
    }

    printf("Minimalni cvor originalnog heap-a: ");
    print_a_star(get_min(&a_star_heap));
    printf("\n");

    destroy_heap(&a_star_heap);
}


/*
Stress test sa 200 nasumicnih elemenata.
*/
void test_10(void)
{
    printf("\n////////////// TEST 10 ///////////////\n\n");

    min_heap_t heap;

    init_min_heap(&heap, 200u, sizeof(int32_t), compare_ints);
    srand(12345u);

    for (size_t i = 0u; i < 200u; i++)
    {
        int32_t value = (rand() % 201) - 100;
        heap_insert(&heap, &value);
    }

    printf("Heap sa 200 elemenata: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    while (!heap_empty(&heap))
    {
        pop_min(&heap);
    }

    printf("Heap nakon brisanja svih elemenata: ");
    heap_dump(&heap, print_ints);
    printf("\n");

    destroy_heap(&heap);
}
