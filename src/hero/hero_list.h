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


HeroList* init_hero_list();
bool resize_hero_list_if_needed(HeroList* list);
bool delete_hero(HeroList* list, Hero* hero);
void free_hero_list(HeroList* list);
bool is_name_valid(HeroList* list, const char* name);

#endif // HERO_LIST_H