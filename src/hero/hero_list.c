#include "hero_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------------------------

HeroListIterator hero_iterator(HeroList* list) {
    HeroListIterator iterator;
    iterator.list = list;
    iterator.current_index = 0;
    return iterator;

}
bool has_next_hero(HeroListIterator* iterator) {
    return iterator->current_index < iterator->list->count;
}
Hero* get_next_hero(HeroListIterator* iterator) {
    if (!has_next_hero(iterator)) {
        return NULL;
    }
    return &iterator->list->heroes[iterator->current_index++];
}

// -------------------------------------------------

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

void free_hero_list(HeroList* list) {
    if (list != NULL) {
        free(list->heroes);
        free(list);
    }
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

// -------------------------------------------------

bool is_name_avaliable(HeroList* list, const char* name) {
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

    HeroListIterator iterator = hero_iterator(list);
    while (has_next_hero(&iterator)) {
        Hero* existing_hero = get_next_hero(&iterator);
        if (strcmp(existing_hero->name, name) == 0) {
            return false;
        }
    }

    return true;
}

// -------------------------------------------------

Hero* add_hero(HeroList* list, const char* name, HeroRace race, HeroClass hero_class,
               int experience_level, int reputation, HeroStatus status) {
    if (!resize_hero_list_if_needed(list)) {
        return NULL;
    }

    Hero new_hero = create_hero(name, race, hero_class, experience_level, reputation, status);
    list->heroes[list->count] = new_hero;
    list->count++;
    return &list->heroes[list->count - 1];
}

Hero* add_hero_direct(HeroList* list, Hero* hero) {
    if (!resize_hero_list_if_needed(list)) {
        return NULL;
    }

    list->heroes[list->count] = *hero;
    list->count++;
    return &list->heroes[list->count - 1];
}

Hero* find_hero(HeroList* list, HeroFilterFunc filter, const void* state) {
    HeroListIterator iterator = hero_iterator(list);
    while (has_next_hero(&iterator)) {
        Hero* hero = get_next_hero(&iterator);
        if (filter(hero, state)) {
            return hero;
        }
    }
    return NULL;
}

HeroList* filter_heroes(HeroList* list, HeroFilterFunc filter, const void* state) {
    if (list == NULL || filter == NULL) {
        return NULL;
    }
    
    HeroList* filtered_list = init_hero_list();
    if (filtered_list == NULL) {
        return NULL;
    }

    HeroListIterator iterator = hero_iterator(list);
    while (has_next_hero(&iterator)) {
        Hero* hero = get_next_hero(&iterator);
        if (filter(hero, state)) {
            add_hero_direct(filtered_list, hero);
        }
    }

    return filtered_list;
}

HeroList* sort_heroes(HeroList* list, HeroCompareFunc compare, const void* state) {
    if (list == NULL || compare == NULL) {
        return NULL;
    }

    HeroList* sorted_list = init_hero_list();
    if (sorted_list == NULL) {
        return NULL;
    }

    for (int i = 0; i < list->count; i++) {
        add_hero_direct(sorted_list, &list->heroes[i]);
    }

    for (int i = 0; i < sorted_list->count - 1; i++) {
        for (int j = 0; j < sorted_list->count - i - 1; j++) {
            if (!compare(&sorted_list->heroes[j], &sorted_list->heroes[j + 1], state)) {
                Hero temp = sorted_list->heroes[j];
                sorted_list->heroes[j] = sorted_list->heroes[j + 1];
                sorted_list->heroes[j + 1] = temp;
            }
        }
    }

    return sorted_list;
}

void sort_heroes_in_place(HeroList* list, HeroCompareFunc compare, const void* state) {
    if (!list || !compare) return;

    for (int i = 0; i < list->count - 1; i++) {
        for (int j = 0; j < list->count - i - 1; j++) {
            if (!compare(&list->heroes[j], &list->heroes[j + 1], state)) {
                Hero temp = list->heroes[j];
                list->heroes[j] = list->heroes[j + 1];
                list->heroes[j + 1] = temp;
            }
        }
    }
}


bool delete_hero(HeroList* list, Hero* hero) {
    if (list == NULL || hero == NULL) {
        return false;
    }

    if (hero->status == ON_QUEST) {
        printf("Nie mozna wyrejestrowac bohatera, ktory jest na misji.\n");
        return false;
    }

    int index = -1;
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->heroes[i].name, hero->name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Blad: Bohater nie znaleziony na liscie.\n");
        return false;
    }

    for (int i = index; i < list->count - 1; i++) {
        list->heroes[i] = list->heroes[i + 1];
    }
    list->count--;

    return true;
}

bool delete_heroes(HeroList* originalList, HeroList* subsetToDelete) {
    if (originalList == NULL || subsetToDelete == NULL) {
        return false;
    }

    HeroListIterator iterator = hero_iterator(subsetToDelete);
    while (has_next_hero(&iterator)) {
        Hero* heroToDelete = get_next_hero(&iterator);
        if (!delete_hero(originalList, heroToDelete)) {
            return false;
        }
    }

    return true;
}

