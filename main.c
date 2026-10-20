
/*
Vladimir Andrisko RA 95/2023

Zadatak 60: Modul koji predstavlja min heap.
Resenje: 
Modul uz pomoc void* podrzava rad sa vise od jednog tipa. 
Za svaki tip potrebno je napisati compare funkciju i print funkciju.
Korisnik vodi racuna o prekoracenju niza, pogresnom indeksiranju i sl.

API:

typedef struct min_heap{
    size_t size;                                        Trenutna velicina heap-a.
    size_t capacity;                                    Maksimalna velicina heap-a.
    size_t element_size;                                Velicina tipa koji se koristi.
    bool (*compare_cb)(void* elem1, void* elem2);       Funkcija za relaciju poredjenja tipa.
    void* data;                                         Podaci.
} min_heap_t;


Inicijalizuje heap strukturu.
size - Maksimalna velicina heap-a,
element_size - Velicina tipa koji se koristi.
bool (*compare)(void* elem1, void* elem2) - Pokazivac na funkciju za relaciju poredjenja.

Compare funkcija treba da vrati true ako je prvi element manji od drugog.
Primer:

bool compare_ints(void* elem1, void* elem2)
{
    int32_t x = *(int32_t*)elem1;
    int32_t y = *(int32_t*)elem2;

    return x < y;
}

Proizvod size i element_size ne sme prekoraciti maksimalnu vrednost tipa size_t.
Za element_size preporuceno je koristi operator sizeof(), osim ako korisnik zna sta radi.
Pogresno prosledjena velicina elementa moze da izazove nedefinisano ponasanje.

Funkcija sadrzi malloc() kako bi se alocirala trazena memorija, zbog toga je preporuceno pozvati ovu f-ju u fazi inicijalizacije
kako bi se izbegla spora alkoacija za potrebu realnog vremena i kako bi se mogle detektovati greske.

Vraca 1 ako je heap uspesno inicijalizovan, 0 ako nije.

size_t init_min_heap(min_heap_t* heap_structure, size_t size, size_t element_size, bool (*compare)(void* elem1, void* elem2));

----------------------------------------------

Pravi heap strukturu od datog niza.

heap - Inicijalizovana heap struktura.
arr - niz elemanata koji se smesta u heap.
arr_size - Broj elemenata u prosledjenom nizu.

Potrebno je da korisnik vodi racuna o tome da arr_size nije veci od maksimalne velicine heap-a koji je prosledjen.
arr_size mora biti veci od nule. 

void build_heap(min_heap_t* heap, const void* arr, size_t arr_size);

----------------------------------------------

Oslobadja memoriju zauzetu pri inicijalizaciji, pozvati u paru sa init_min_heap.

void destroy_heap(const min_heap_t* heap);

----------------------------------------------

Ubacuje novi element u prosledjenu heap strukturu. 

Korisnik vodi racuna o tome da ne premasi maksimalnu velicinu heap-a.
elem mora biti validan pokazivac na element odgovarajuceg tipa.

void heap_insert(min_heap_t* heap, const void* elem);

----------------------------------------------

Brise element sa datim indeksom iz heap strukture.

Korisnik vodi racuna da index bude manji od trenutne velicine heap-a.

void heap_delete(min_heap_t* heap, size_t index);

----------------------------------------------

Vraca pokazivac na element na pocetku heap strukture (minimalni element).
Potrebno je napraviti konverziju za element na tip od prosledjene heap strukture.

Vraca nullptr ako je heap prazan.

void* get_min(const min_heap_t* heap);

----------------------------------------------

Brise minimalni element iz prosledjene heap strukture.

Heap ne sme biti prazan, proveriti pomocu heap_empty() funkcije.

void pop_min(min_heap_t* heap);

----------------------------------------------

Iterira kroz heap strukturu i koristi prosledjenu funkciju print_cb za ispis strukture.
print_cb omogucava da funkcija bude nezavisna od platforme, tj. od nacina ispisivanja podataka.

Elementi se ispisuju redosledom kojim su smesteni u heap-u.

primer print_cb funkcije:
void print_a_star(void* elem)
{
    a_star_node_t x = *(a_start_node_t*)elem;
    printf("Node id: %"PRIdLEAST16", f: %.2lf, h: %.2lf | ", x.id, x.f_cost, x.h_cost);
}

void heap_dump(const min_heap_t* heap, void (*print_cb)(void* elem));

----------------------------------------------

Sortira podatke iz prosledjene heap strukture u opadajucem redosledu
i smesta ih u prosledjeni niz arr.

Korisnik vodi racuna da arr ima dovoljno memorije za sve elemente heap-a.
arr ne sme da se preklapa sa memorijom heap-a.

Originalna heap struktura ostaje nepromenjena i moze se koristiti nakon sortiranja.

void heap_sort(const min_heap_t* heap, void* arr);

----------------------------------------------

Vraca 1 ako je heap struktura prazna, 0 inace.

bool heap_empty(const min_heap_t* heap);

----------------------------------------------

Vraca 1 ako je heap struktura popunjena do maksimuma, 0 inace.

bool heap_full(const min_heap_t* heap);

----------------------------------------------

Obrise sve podatke iz heap strukture. 
Napomena: Ne oslobadja memoriju alociranu u init_min_heap.

void clear_heap(min_heap_t* heap);

----------------------------------------------

MISRA - Ignorisana pravila:

5.6 
Savetno pravilo, nema uticaj na funkcionalnost programa.

5.7
Dozvoljeno ponovno koriscenje naziva lokalnih promenljivih i
parametara u razlicitim funkcijama radi jednostavnosti koda.

20.4
Dozvoljena dinamicka alokacija memorije pomocu malloc().
Alokacija se izvrsava samo prilikom inicijalizacije heap-a,
kako ne bi uticala na izvrsavanje operacija u realnom vremenu.

malloc() se nalazi samo u init_min_heap() funkciji.

17.4
Dozvoljena pokazivacka aritmetika za pristup elementima
generickog niza. Koristi se unsigned char* kako bi se
izracunala adresa elementa na osnovu njegove velicine i indeksa.

Koristi se u swap() i get_element() funkcijama, ali te funkcije
nisu dostupne u API.

13.5
Prijavljuje gresku za inicijalizaciju promenljive i u for petlji.
Dati MISRA koristi ISO/IEC 9899:1990 standard C-a koji nema definisanu
deklaraciju promenljive unutar for petlje.

10.1
Ignorisane implicitne konverzije koje analizator pogresno
prijavljuje prilikom koriscenja assert() makroa.

Prenosivost:

Na hosted C23 okruzenjima ceo kod je prenosiv.

Na freestanding C23 okruzenjima, malloc, free i assert funkcije su
jedini neprenosivi delovi koda.

*/

#include "min_heap.h"
#include "test.h"
#include <stdio.h>

int main(void)
{  
    
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    test_8();
    test_9();
    test_10();

    return 0;
}
