#ifndef HERO_LIST_H
#define HERO_LIST_H

#include <stdbool.h>

#include "hero.h"

/**
 * Typ funkcji filtrującej bohaterów.
 * Zwraca true, jeśli bohater spełnia warunki filtra.
 * Zwraca false w przeciwnym wypadku.
 *
 * const Hero* hero - Bohater do sprawdzenia.
 * const void* state - Dodatkowy stan przekazywany do funkcji filtrujacej.
 */
typedef bool (*HeroFilterFunc)(const Hero*, const void* state);

/**
 * Typ funkcji porównującej dwóch bohaterów.
 * Zwraca true, jeśli pierwszy bohater powinien być przed drugim 
 * w posortowanej kolejności. Zwraca false w przeciwnym wypadku.
 *
 * const Hero* a - Pierwszy bohater.
 * const Hero* b - Drugi bohater.
 * const void* state - Dodatkowy stan przekazywany do funkcji porownujacej.
 */
typedef bool (*HeroCompareFunc)(const Hero*, const Hero*, const void* state);

/**
 * Węzeł listy powiązanej do przechowywania wskaźnika do bohatera.
 */
typedef struct HeroNode {
    Hero* hero;                 // Wskaźnik do bohatera
    struct HeroNode* next;      // Wskaźnik do następnego węzła
} HeroNode;

/**
 * Struktura reprezentująca listę powiązaną bohaterów.
 * Obsługuje wskaźniki do bohaterów bez tworzenia kopii.
 * 
 * is_root:
 *   - true = główna lista (uwalnia pamięć bohaterów w free_hero_list)
 *   - false = podzbiór głównej listy (nie uwalnia bohaterów)
 */
typedef struct {
    HeroNode* head;     // Wskaźnik na pierwszy węzeł
    int count;          // Liczba bohaterów w liście
    bool is_root;       // true = główna lista (uwalna bohaterów), false = podzbiór
} HeroList;

/**
 * Struktura iteratora do przechodzenia po liście bohaterów.
 */
typedef struct {
    HeroNode* current_node;     // Wskaźnik na bieżący węzeł
} HeroListIterator;


// -------------------------------------------------


/**
 * Funkcja tworząca iterator dla listy bohaterów.
 *
 * HeroList* list - Wskaźnik do listy.
 * 
 * Funkcja zwraca iterator ustawiony na początek listy.
 */
HeroListIterator hero_iterator(HeroList* list);

/**
 * Funkcja sprawdzająca czy w iteratorze istnieje następny bohater.
 *
 * HeroListIterator* iterator - Wskaźnik na iterator.
 * 
 * Funkcja zwraca true jeśli istnieje następny bohater, false jeśli koniec listy.
 */
bool has_next_hero(HeroListIterator* iterator);

/**
 * Funkcja pobierająca następnego bohatera i postępująca iterator.
 *
 * HeroListIterator* iterator - Wskaźnik na iterator.
 * 
 * Funkcja zwraca wskaźnik do kolejnego bohatera lub NULL jeśli koniec listy.
 */
Hero* get_next_hero(HeroListIterator* iterator);

// -------------------------------------------------

// -------------------------------------------------

/**
 * Funkcja inicjalizująca nową listę bohaterów.
 * 
 * Funkcja zwraca wskaźnik do nowej listy lub NULL jeśli błąd alokacji.
 * Zwrócona lista ma is_root = true.
 */
HeroList* init_hero_list();

/**
 * Funkcja uwalniająca pamięć listy bohaterów.
 *
 * HeroList* list - Wskaźnik do listy (może być NULL).
 * 
 * Jeśli is_root==true, uwalnia również pamięć wszystkich bohaterów.
 * Jeśli is_root==false, uwalnia tylko strukturę listy (bohaterowie są na głównej liście).
 * 
 * Funkcja nic nie zwraca.
 */
void free_hero_list(HeroList* list);


// -------------------------------------------------


/**
 * Funkcja sprawdzająca czy imię bohatera jest dostępne (unikalne).
 *
 * HeroList* list - Wskaźnik do listy.
 * const char* name - Imię do sprawdzenia.
 * 
 * Funkcja zwraca true jeśli imię jest dostępne i prawidłowe.
 * Zwraca false jeśli imię już istnieje lub jest puste.
 */
bool is_name_avaliable(HeroList* list, const char* name);

/**
 * Funkcja dodająca nowego bohatera do listy.
 * Bohaterów można dodawać tylko do głównej listy (list->is_root == true).
 *
 * HeroList* list - Wskaźnik do głównej listy.
 * const char* name - Unikalne imię bohatera.
 * HeroRace race - Rasa bohatera.
 * HeroClass hero_class - Klasa/profesja bohatera.
 * int experience_level - Poziom doświadczenia (1-100).
 * int reputation - Reputacja (0-100).
 * HeroStatus status - Status bohatera.
 * 
 * Funkcja zwraca wskaźnik do nowego bohatera lub NULL jeśli błąd.
 */
Hero* add_hero(HeroList* list, const char* name, HeroRace race, HeroClass hero_class,
               int experience_level, int reputation, HeroStatus status);

/**
 * Funkcja usuwająca bohatera z głównej listy.
 *
 * HeroList* list - Główna lista (musi mieć is_root==true).
 * Hero* hero - Bohater do usunięcia.
 * 
 * Blokuje usuwanie bohatera ze statusem ON_QUEST (na misji).
 * Uwalnia pamięć usuniętego bohatera.
 * 
 * Funkcja zwraca true jeśli usunięcie powiodło się, false w przypadku błędu.
 */
bool delete_hero(HeroList* list, Hero* hero);

/**
 * Funkcja usuwająca wiele bohaterów z głównej listy.
 *
 * HeroList* originalList - Główna lista.
 * HeroList* subsetToDelete - Lista (podzbiór) bohaterów do usunięcia.
 * 
 * Iteruje po subsetToDelete i usuwa każdego bohatera z originalList.
 * Funkcja zwraca true jeśli operacja powiodła się.
 */
bool delete_heroes(HeroList* originalList, HeroList* subsetToDelete);


// -------------------------------------------------


/**
 * Funkcja znajdujaca pierwszego bohatera spełniającego warunki filtra.
 *
 * HeroList* list - Lista do przeszukania.
 * HeroFilterFunc filter - Funkcja filtrująca.
 * const void* state - Stan filtra.
 * 
 * Funkcja zwraca wskaźnik do pierwszego znalezionego bohatera lub NULL.
 */
Hero* find_hero(HeroList* list, HeroFilterFunc filter, const void* state);

/**
 * Funkcja filtrująca listę bohaterów i tworząca nową listę (podzbiór).
 *
 * HeroList* list - Lista do filtrowania.
 * HeroFilterFunc filter - Funkcja filtrująca.
 * const void* state - Stan filtra.
 * 
 * Zwrócona lista jest podzbiorem (is_root==false) - nie zawiera kopii bohaterów.
 * Po zakończeniu użytkowania należy ją uwolnić free_hero_list().
 * 
 * Funkcja zwraca wskaźnik do nowego podzbioru.
 */
HeroList* filter_heroes(HeroList* list, HeroFilterFunc filter, const void* state);

/**
 * Funkcja sortująca listę bohaterów i tworząca nową listę (podzbiór).
 *
 * HeroList* list - Lista do sortowania.
 * HeroCompareFunc compare - Funkcja porównująca.
 * const void* state - Stan sortowania (np. kierunek rosnąco/malejąco).
 * 
 * Zwrócona lista jest podzbiorem (is_root==false) - nie zawiera kopii bohaterów.
 * Po zakończeniu użytkowania należy ją uwolnić free_hero_list().
 * 
 * Funkcja zwraca wskaźnik do nowego podzbioru.
 */
HeroList* sort_heroes(HeroList* list, HeroCompareFunc compare, const void* state);

#endif // HERO_LIST_H
