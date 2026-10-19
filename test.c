#include "test.h"

#define MAX_VALUE 100

/* Ints */
void init_random_arr(int32_t arr[], int32_t size)
{
    printf("Pocetni niz: ");
    for (int32_t i = 0; i < size; i++)
    {
        arr[i] = (rand() % MAX_VALUE) - MAX_VALUE/4;
        printf("%"PRId32", ", arr[i]);
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
    printf("%"PRId32",", *(int32_t*)elem);
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
    printf("%f,", *(float*)elem);
}

/* Example struct */
typedef struct a_start_node{
    int_least16_t id;
    double f_cost;
    double h_cost;
    double g_cost;
} a_start_node_t;

bool compare_a_star(void* elem1, void* elem2)
{
    a_start_node_t x = *(a_start_node_t*)elem1;
    a_start_node_t y = *(a_start_node_t*)elem2;

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
    a_start_node_t x = *(a_start_node_t*)elem;
    printf("Node id: %"PRIdLEAST16", f: %.2lf, h: %.2lf | ", x.id, x.f_cost, x.h_cost);
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

/*
    Testiranje int32_t sa dupliranim elementima.
    Brisanje poslednjeg elementa i vadjenje svih elemenata po redu.
*/
void test_6()
{
    printf("\n////////////// TEST 6 ///////////////\n\n");

    min_heap_t heap;
    int32_t arr[8] = {-4, 7, 7, 0, 20, -4, 3, 12};

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
        int32_t min = *(int32_t*)get_min(&heap);
        printf("%"PRId32",", min);
        pop_min(&heap);
    }
    printf("\n");

    destroy_heap(&heap);
}

/*
    Testiranje heap strukture sa float tipom.
    Ubacivanje elemenata, uzimanje minimuma i brisanje elemenata.
*/
void test_7()
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
void test_8()
{
    printf("\n////////////// TEST 8 ///////////////\n\n");

    min_heap_t heap;

    a_start_node_t arr[6] = {
        {1, 6.0, 3.0, 3.0},
        {2, 4.0, 2.0, 2.0},
        {3, 4.0, 1.0, 3.0},
        {4, 9.0, 5.0, 4.0},
        {5, 4.0, 3.0, 1.0},
        {6, 1.0, 0.5, 0.5}
    };

    init_min_heap(&heap, 10u, sizeof(a_start_node_t), compare_a_star);
    build_heap(&heap, arr, 6u);

    printf("Inicijalni heap: ");
    heap_dump(&heap, print_a_star);
    printf("\n");

    printf("Minimalni cvor: ");
    print_a_star(get_min(&heap));
    printf("\n");

    heap_delete(&heap, 3u);

    a_start_node_t new_node = {7, 2.0, 1.0, 1.0};
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
void test_9()
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

    a_start_node_t nodes[5] = {
        {1, 8.0, 4.0, 4.0},
        {2, 3.0, 2.0, 1.0},
        {3, 3.0, 1.0, 2.0},
        {4, 10.0, 7.0, 3.0},
        {5, 1.0, 0.5, 0.5}
    };

    a_start_node_t sorted_nodes[5];

    init_min_heap(&a_star_heap, 5u, sizeof(a_start_node_t), compare_a_star);
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
    Stress test sa nasumicnim ubacivanjem i brisanjem elemenata.
    Provera heap svojstva i minimalnog elementa nakon svake operacije.
*/
void test_10()
{
    printf("\n////////////// TEST 10 ///////////////\n\n");

    min_heap_t heap;
    int32_t reference[96];
    size_t reference_size = 0u;
    bool passed = true;
    size_t completed = 0u;

    init_min_heap(&heap, 96u, sizeof(int32_t), compare_ints);
    srand(12345u);

    for (size_t i = 0u; i < 5000u; i++)
    {
        int action = rand() % 4;

        if (((action < 2) && !heap_full(&heap)) || heap_empty(&heap))
        {
            int32_t value = (int32_t)((rand() % 201) - 100);

            heap_insert(&heap, &value);
            reference[reference_size] = value;
            reference_size++;
        }
        else if (!heap_empty(&heap))
        {
            size_t index = 0u;

            if (action == 3)
            {
                index = (size_t)rand() % heap.size;
            }

            int32_t removed = ((int32_t*)heap.data)[index];

            if (action == 3)
            {
                heap_delete(&heap, index);
            }
            else
            {
                pop_min(&heap);
            }

            size_t j = 0u;

            while ((j < reference_size) && (reference[j] != removed))
            {
                j++;
            }

            if (j < reference_size)
            {
                reference[j] = reference[reference_size - 1u];
                reference_size--;
            }
            else
            {
                passed = false;
            }
        }

        if (heap.size != reference_size)
        {
            passed = false;
        }

        for (size_t j = 1u; j < heap.size; j++)
        {
            size_t parent = (j - 1u) / 2u;

            int32_t parent_value = ((int32_t*)heap.data)[parent];
            int32_t child_value = ((int32_t*)heap.data)[j];

            if (parent_value > child_value)
            {
                passed = false;
            }
        }

        if (reference_size > 0u)
        {
            int32_t min = reference[0];

            for (size_t j = 1u; j < reference_size; j++)
            {
                if (reference[j] < min)
                {
                    min = reference[j];
                }
            }

            if (*(int32_t*)get_min(&heap) != min)
            {
                passed = false;
            }
        }
        else if (get_min(&heap) != nullptr)
        {
            passed = false;
        }

        completed++;

        if (!passed)
        {
            break;
        }
    }

    printf("Izvrseno operacija: %zu\n", completed);
    printf("Konacna velicina heap-a: %zu\n", heap.size);
    printf("Rezultat: %s\n", passed ? "PASS" : "FAIL");

    destroy_heap(&heap);
}

/*
    Testiranje razlicitih velicina heap-a.
    Sortirani, obrnuto sortirani nizovi i nizovi sa duplikatima.
*/
void test_11()
{
    printf("\n////////////// TEST 11 ///////////////\n\n");

    const size_t sizes[] = {
        1u, 2u, 3u, 7u, 8u, 9u,
        31u, 32u, 33u, 63u, 64u, 65u,
        127u, 128u, 129u
    };

    int32_t arr[129];
    int32_t sorted[129];
    min_heap_t heap;

    bool passed = true;
    size_t completed = 0u;

    init_min_heap(&heap, 129u, sizeof(int32_t), compare_ints);

    for (size_t pattern = 0u; pattern < 3u; pattern++)
    {
        for (size_t c = 0u; c < sizeof(sizes)/sizeof(sizes[0]); c++)
        {
            size_t n = sizes[c];

            for (size_t i = 0u; i < n; i++)
            {
                if (pattern == 0u)
                {
                    arr[i] = (int32_t)i - 64;
                }
                else if (pattern == 1u)
                {
                    arr[i] = (int32_t)(n - i) - 64;
                }
                else
                {
                    arr[i] = (int32_t)((i * 17u + n * 13u) % 9u) - 4;
                }
            }

            build_heap(&heap, arr, n);
            heap_sort(&heap, sorted);

            int32_t min = arr[0];

            for (size_t i = 1u; i < n; i++)
            {
                if (arr[i] < min)
                {
                    min = arr[i];
                }

                if (sorted[i - 1u] < sorted[i])
                {
                    passed = false;
                }
            }

            if ((heap.size != n) ||
                (*(int32_t*)get_min(&heap) != min) ||
                (sorted[n - 1u] != min))
            {
                passed = false;
            }

            completed++;

            if (!passed)
            {
                printf("Greska za n = %zu, pattern = %zu\n", n, pattern);
                break;
            }
        }

        if (!passed)
        {
            break;
        }
    }

    printf("Testiranih kombinacija: %zu\n", completed);
    printf("Rezultat: %s\n", passed ? "PASS" : "FAIL");

    destroy_heap(&heap);
}

/*
    Brisanje svakog moguceg indeksa iz heap strukture.
    Poredjenje elemenata pre i nakon brisanja pomocu heap_sort.
*/
void test_12()
{
    printf("\n////////////// TEST 12 ///////////////\n\n");

    min_heap_t heap;
    int32_t arr[40];
    int32_t expected[40];
    int32_t result[40];

    bool passed = true;
    size_t completed = 0u;

    init_min_heap(&heap, 40u, sizeof(int32_t), compare_ints);

    for (size_t n = 1u; (n <= 40u) && passed; n++)
    {
        for (size_t i = 0u; i < n; i++)
        {
            arr[i] = (int32_t)((i * 31u + n * 7u) % 17u) - 8;
        }

        for (size_t index = 0u; index < n; index++)
        {
            build_heap(&heap, arr, n);
            heap_sort(&heap, expected);

            int32_t removed = ((int32_t*)heap.data)[index];

            heap_delete(&heap, index);
            heap_sort(&heap, result);

            bool skipped = false;
            size_t j = 0u;

            for (size_t i = 0u; i < n; i++)
            {
                if ((!skipped) && (expected[i] == removed))
                {
                    skipped = true;
                }
                else
                {
                    if ((j >= heap.size) || (result[j] != expected[i]))
                    {
                        passed = false;
                    }

                    j++;
                }
            }

            if ((!skipped) || (j != heap.size))
            {
                passed = false;
            }

            for (size_t i = 1u; i < heap.size; i++)
            {
                size_t parent = (i - 1u) / 2u;

                if (((int32_t*)heap.data)[parent] >
                    ((int32_t*)heap.data)[i])
                {
                    passed = false;
                }
            }

            completed++;

            if (!passed)
            {
                printf("Greska za n = %zu, index = %zu\n", n, index);
                break;
            }
        }
    }

    printf("Testiranih brisanja: %zu\n", completed);
    printf("Rezultat: %s\n", passed ? "PASS" : "FAIL");

    destroy_heap(&heap);
}


/*
    Testiranje float tipa sa velikim i malim vrednostima.
    Pozitivna i negativna nula, duplikati i provera redosleda.
*/
void test_13()
{
    printf("\n////////////// TEST 13 ///////////////\n\n");

    float arr[] = {
        0.0f, -0.0f, 1.0e30f, -1.0e30f,
        1.0e-30f, -1.0e-30f, 3.5f, -3.5f,
        7.125f, 7.125f, -20.75f, 100.0f,
        0.001f, -0.001f, 5.0f
    };

    size_t n = sizeof(arr) / sizeof(arr[0]);
    float sorted[sizeof(arr) / sizeof(arr[0])];

    min_heap_t heap;
    bool passed = true;

    init_min_heap(&heap, n, sizeof(float), compare_floats);
    build_heap(&heap, arr, n);

    float initial_min = *(float*)get_min(&heap);

    heap_sort(&heap, sorted);

    printf("Sortiran niz: ");
    for (size_t i = 0u; i < n; i++)
    {
        print_floats(&sorted[i]);

        if ((i > 0u) && (sorted[i - 1u] < sorted[i]))
        {
            passed = false;
        }
    }
    printf("\n");

    if ((heap.size != n) || (*(float*)get_min(&heap) != initial_min))
    {
        passed = false;
    }

    for (size_t i = 0u; i < n; i++)
    {
        size_t count_arr = 0u;
        size_t count_sorted = 0u;

        for (size_t j = 0u; j < n; j++)
        {
            if (arr[j] == arr[i])
            {
                count_arr++;
            }

            if (sorted[j] == arr[i])
            {
                count_sorted++;
            }
        }

        if (count_arr != count_sorted)
        {
            passed = false;
        }
    }

    float previous = *(float*)get_min(&heap);

    while (!heap_empty(&heap))
    {
        float current = *(float*)get_min(&heap);

        if (current < previous)
        {
            passed = false;
        }

        previous = current;
        pop_min(&heap);
    }

    if (get_min(&heap) != nullptr)
    {
        passed = false;
    }

    printf("Rezultat: %s\n", passed ? "PASS" : "FAIL");

    destroy_heap(&heap);
}

/*
    Testiranje A* strukture sa jednakim f_cost vrednostima.
    Provera h_cost prioriteta i integriteta podataka nakon sortiranja.
*/
void test_14()
{
    printf("\n////////////// TEST 14 ///////////////\n\n");

    a_start_node_t nodes[12] = {
        {1,  5.0, 3.0, 2.0},
        {2,  5.0, 1.0, 4.0},
        {3,  3.0, 2.0, 1.0},
        {4,  3.0, 1.0, 2.0},
        {5,  3.0, 1.0, 2.0},
        {6,  7.0, 4.0, 3.0},
        {7,  2.0, 1.0, 1.0},
        {8,  2.0, 0.0, 2.0},
        {9,  2.0, 0.0, 2.0},
        {10, 8.0, 2.0, 6.0},
        {11, 5.0, 1.0, 4.0},
        {12, 0.0, 0.0, 0.0}
    };

    a_start_node_t sorted[12];
    min_heap_t heap;
    bool passed = true;

    init_min_heap(&heap, 12u, sizeof(a_start_node_t), compare_a_star);
    build_heap(&heap, nodes, 12u);

    a_start_node_t initial_min = *(a_start_node_t*)get_min(&heap);

    heap_sort(&heap, sorted);

    printf("Sortirani A* cvorovi:\n");

    for (size_t i = 0u; i < 12u; i++)
    {
        print_a_star(&sorted[i]);
        printf("\n");

        if (i > 0u)
        {
            if (compare_a_star(&sorted[i - 1u], &sorted[i]))
            {
                passed = false;
            }
        }

        bool found = false;

        for (size_t j = 0u; j < 12u; j++)
        {
            if (sorted[i].id == nodes[j].id)
            {
                if ((sorted[i].f_cost == nodes[j].f_cost) &&
                    (sorted[i].h_cost == nodes[j].h_cost) &&
                    (sorted[i].g_cost == nodes[j].g_cost))
                {
                    found = true;
                }

                break;
            }
        }

        if (!found)
        {
            passed = false;
        }
    }

    a_start_node_t current_min = *(a_start_node_t*)get_min(&heap);

    if ((heap.size != 12u) || (current_min.id != initial_min.id))
    {
        passed = false;
    }

    a_start_node_t previous;
    bool first = true;

    while (!heap_empty(&heap))
    {
        a_start_node_t current = *(a_start_node_t*)get_min(&heap);

        if (!first)
        {
            if (compare_a_star(&current, &previous))
            {
                passed = false;
            }
        }

        previous = current;
        first = false;

        pop_min(&heap);
    }

    printf("Rezultat: %s\n", passed ? "PASS" : "FAIL");

    destroy_heap(&heap);
}

/*
    Visestruko koriscenje iste heap strukture.
    Testiranje clear_heap, ponovnog ubacivanja, brisanja i sortiranja.
    Provera da heap_sort ne upisuje izvan granica izlaznog niza.
*/
void test_15()
{
    printf("\n////////////// TEST 15 ///////////////\n\n");

    min_heap_t heap;
    int32_t guarded[34];

    bool passed = true;
    size_t completed = 0u;

    init_min_heap(&heap, 32u, sizeof(int32_t), compare_ints);

    for (size_t cycle = 0u; cycle < 300u; cycle++)
    {
        clear_heap(&heap);

        guarded[0] = INT32_MIN;
        guarded[33] = INT32_MAX;
        guarded[1] = 123456;

        heap_sort(&heap, &guarded[1]);

        if ((guarded[0] != INT32_MIN) ||
            (guarded[33] != INT32_MAX) ||
            (guarded[1] != 123456))
        {
            passed = false;
        }

        size_t count = (cycle % 32u) + 1u;

        for (size_t i = 0u; i < count; i++)
        {
            int32_t value =
                (int32_t)((cycle * 17u + i * 29u) % 201u) - 100;

            heap_insert(&heap, &value);
        }

        if ((heap.size != count) ||
            ((count == 32u) && !heap_full(&heap)))
        {
            passed = false;
        }

        heap_sort(&heap, &guarded[1]);

        if ((guarded[0] != INT32_MIN) ||
            (guarded[33] != INT32_MAX))
        {
            passed = false;
        }

        for (size_t i = 1u; i < count; i++)
        {
            if (guarded[i] < guarded[i + 1u])
            {
                passed = false;
            }
        }

        if (*(int32_t*)get_min(&heap) != guarded[count])
        {
            passed = false;
        }

        size_t index = cycle % heap.size;
        heap_delete(&heap, index);

        int32_t new_value = (int32_t)(cycle % 51u) - 25;
        heap_insert(&heap, &new_value);

        for (size_t i = 1u; i < heap.size; i++)
        {
            size_t parent = (i - 1u) / 2u;

            if (((int32_t*)heap.data)[parent] >
                ((int32_t*)heap.data)[i])
            {
                passed = false;
            }
        }

        clear_heap(&heap);

        if ((!heap_empty(&heap)) || (get_min(&heap) != nullptr))
        {
            passed = false;
        }

        completed++;

        if (!passed)
        {
            printf("Greska u ciklusu: %zu\n", cycle);
            break;
        }
    }

    printf("Izvrseno ciklusa: %zu\n", completed);
    printf("Rezultat: %s\n", passed ? "PASS" : "FAIL");

    destroy_heap(&heap);
}
