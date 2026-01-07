#ifndef HERO_LIST_H
#define HERO_LIST_H

#include <stdbool.h>

#include "hero.h"
/**
 * Funkcja filtrujaca bohaterow.
 * Zwraca true, jesli bohater spelnia warunki filtra.
 * Zwraca false w przeciwnym wypadku.
 */
typedef bool (*HeroFilterFunc)(const Hero*, void* state);

/**
 * Funkcja porownujaca dwoch bohaterow.
 * Zwraca true, jesli pierwszy bohater powinien byc przed drugim w posortowanej kolejnosci.
 * Zwraca false w przeciwnym wypadku.
 */
typedef bool (*HeroCompareFunc)(const Hero*, const Hero*, void* state);

// -------------------------------------------------

typedef struct {
    Hero *heroes;
    int count;
    int capacity;
    int next_id;
} HeroList;

typedef struct {
    HeroList* list;
    int current_index;
} HeroListIterator;

// -------------------------------------------------

HeroListIterator hero_iterator(HeroList* list);
bool has_next_hero(HeroListIterator* iterator);
Hero* get_next_hero(HeroListIterator* iterator);

// -------------------------------------------------

HeroList* init_hero_list();
void free_hero_list(HeroList* list);

// -------------------------------------------------

bool is_name_avaliable(HeroList* list, const char* name);

// -------------------------------------------------

Hero* add_hero(HeroList* list, const char* name, HeroRace race, HeroClass hero_class,
               int experience_level, int reputation, HeroStatus status);
bool delete_hero(HeroList* list, Hero* hero);
bool delete_heroes(HeroList* originalList, HeroList* subsetToDelete);

// -------------------------------------------------

Hero* find_hero(HeroList* list, HeroFilterFunc filter, void* state); 
HeroList* filter_heroes(HeroList* list, HeroFilterFunc filter, void* state);
HeroList* sort_heroes(HeroList* list, HeroCompareFunc compare, void* state);


#endif // HERO_LIST_H