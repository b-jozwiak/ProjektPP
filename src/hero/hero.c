#include "hero.h"
#include <stdlib.h>

HeroList* init_hero_list() {
    HeroList* list = (HeroList*)malloc(sizeof(HeroList));
    if (list == NULL) {
        return NULL;
    }
    list->capacity = 10;
    list->count = 0;
    list->next_id = 1;
    list->heroes = (Hero*)malloc(sizeof(Hero) * list->capacity);

    if (list->heroes == NULL) {
        free(list);
        return NULL;
    }

    return list;
}

void resize_hero_list_if_needed(HeroList* list) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->heroes = (Hero*)realloc(list->heroes, sizeof(Hero) * list->capacity);
    }
}

void free_hero_list(HeroList* list) {
    if (list != NULL) {
        free(list->heroes);
        free(list);
    }
}