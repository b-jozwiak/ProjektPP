#ifndef HERO_LIST_H
#define HERO_LIST_H

#include <stdbool.h>

#include "hero.h"

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

HeroListIterator hero_iterator(HeroList* list);
bool has_next_hero(HeroListIterator* iterator);
Hero* get_next_hero(HeroListIterator* iterator);


HeroList* init_hero_list();
bool resize_hero_list_if_needed(HeroList* list);
bool delete_hero(HeroList* list, Hero* hero);
void free_hero_list(HeroList* list);
bool is_name_avaliable(HeroList* list, const char* name);

#endif // HERO_LIST_H