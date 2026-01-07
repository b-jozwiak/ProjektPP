#include "hero_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

bool is_name_valid(const char* name) {
    if (name == NULL) {
        return false;
    }

    int length = 0;
    while (name[length] != '\0') {
        length++;
        if (length > MAX_HERO_NAME_LENGTH) {
            return false;
        }
    }

    if (length == 0) {
        return false;
    }



    return true;
}

bool resize_hero_list_if_needed(HeroList* list) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        Hero* temp = (Hero*)realloc(list->heroes, sizeof(Hero) * new_capacity);
        if (temp == NULL) {
            fprintf(stderr, "Blad powiekszenia listy bohaterow.\n");
            return false;
        }
        list->capacity = new_capacity;
        list->heroes = temp;
    }

    return true;
}

bool delete_hero(HeroList* list, Hero* hero) {
    if (list == NULL || hero == NULL) {
        return false;
    }

    int index = -1;
    for (int i = 0; i < list->count; i++) {
        if (&list->heroes[i] == hero) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return false;
    }

    for (int i = index; i < list->count - 1; i++) {
        list->heroes[i] = list->heroes[i + 1];
    }
    list->count--;

    return true;
}


void free_hero_list(HeroList* list) {
    if (list != NULL) {
        free(list->heroes);
        free(list);
    }
}