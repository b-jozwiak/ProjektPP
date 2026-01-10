#include "hero_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------------------------

HeroListIterator hero_iterator(HeroList* list) {
    HeroListIterator iterator = {list, 0};
    return iterator;

}
bool has_next_hero(HeroListIterator* iterator) {
    return iterator->current_index < iterator->list->count;
}
Hero* get_next_hero(HeroListIterator* iterator) {
    if (!has_next_hero(iterator)) {
        return NULL;
    }
    return iterator->list->heroes[iterator->current_index++];
}

// -------------------------------------------------

HeroList* init_hero_list() {
    HeroList* list = (HeroList*)malloc(sizeof(HeroList));
    if (list == NULL) {
        return NULL;
    }
    list->capacity = 10;
    list->count = 0;
    list->heroes = malloc(sizeof(Hero*) * list->capacity);
    list->is_root = true;

    if (list->heroes == NULL) {
        free(list);
        return NULL;
    }

    return list;
}

void free_hero_list(HeroList* list) {
    if (list != NULL) {
        if (list->is_root) {
            for (int i = 0; i < list->count; i++) {
                free(list->heroes[i]);
            }
        }
        free(list->heroes);
        free(list);
    }
}

bool resize_hero_list_if_needed(HeroList* list) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity * 2;
        Hero** temp = realloc(list->heroes, sizeof(Hero*) * new_capacity);
        if (temp == NULL) {
            fprintf(stderr, "Blad powiekszenia listy bohaterow.\n");
            return false;
        }
        list->heroes = temp;
        list->capacity = new_capacity;
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

Hero create_hero(const char* name, HeroRace race, HeroClass hero_class, int experience_level, int reputation, HeroStatus status) {
    Hero hero;
    
    if (name == NULL || strlen(name) == 0 || strlen(name) > MAX_HERO_NAME_LENGTH) {
        fprintf(stderr, "Blad: Nieprawidlowe imie bohatera.\n");
        hero.name[0] = '\0';
        return hero;
    }
    
    if (experience_level < 1) {
        fprintf(stderr, "Blad: Poziom doswiadczenia musi byc >= 1.\n");
        experience_level = 1;
    }

    if (reputation < 0 || reputation > 100) {
        fprintf(stderr, "Blad: Reputacja musi byc w zakresie 0-100.\n");
        reputation = 0;
    }
    
    strncpy(hero.name, name, MAX_HERO_NAME_LENGTH);
    hero.name[MAX_HERO_NAME_LENGTH] = '\0';
    hero.race = race;
    hero.hero_class = hero_class;
    hero.experience_level = experience_level;
    hero.reputation = reputation;
    hero.status = status;
    
    return hero;
}

Hero* add_hero(HeroList* list, const char* name, HeroRace race, HeroClass hero_class,
               int experience_level, int reputation, HeroStatus status) {
    if (list == NULL) {
        return NULL;
    }
    if (list->is_root == false) {
        printf("\n\nDodawanie bohaterow mozna tylko wykonac na oryginalnej liscie.\n\n");
        return NULL;
    }
    if (!resize_hero_list_if_needed(list)) {
        return NULL;
    }

    Hero* new_hero = malloc(sizeof(Hero));
    if (new_hero == NULL) return NULL;
    *new_hero = create_hero(name, race, hero_class, experience_level, reputation, status);
    list->heroes[list->count++] = new_hero;
    return new_hero;
}

/**
 * Dodaje istniejacego bohatera do listy bez tworzenia nowego obiektu.
 * Uzywane przy tworzeniu "widokow" na glowna liste.
 */
Hero* add_hero_direct(HeroList* list, Hero* hero) {
    if (!resize_hero_list_if_needed(list)) {
        return NULL;
    }

    list->heroes[list->count++] = hero;
    return hero;
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
    filtered_list->is_root = false;

    HeroListIterator iterator = hero_iterator(list);
    while (has_next_hero(&iterator)) {
        Hero* hero = get_next_hero(&iterator);
        if (filter(hero, state)) {
            add_hero_direct(filtered_list, hero);
        }
    }

    return filtered_list;
}

void sort_heroes_in_place(HeroList* list, HeroCompareFunc compare, const void* state) {
    if (!list || !compare) return;

    for (int i = 0; i < list->count - 1; i++) {
        for (int j = 0; j < list->count - i - 1; j++) {
            if (!compare(list->heroes[j], list->heroes[j + 1], state)) {
                Hero* temp = list->heroes[j];
                list->heroes[j] = list->heroes[j + 1];
                list->heroes[j + 1] = temp;
            }
        }
    }
}

HeroList* sort_heroes(HeroList* list, HeroCompareFunc compare, const void* state) {
    if (list == NULL || compare == NULL) {
        return NULL;
    }

    HeroList* sorted_list = init_hero_list();
    if (sorted_list == NULL) {
        return NULL;
    }
    sorted_list->is_root = false;

    for (int i = 0; i < list->count; i++) {
        add_hero_direct(sorted_list, list->heroes[i]);
    }

    sort_heroes_in_place(sorted_list, compare, state);
    return sorted_list;
}    

bool delete_hero(HeroList* list, Hero* hero) {
    if (list == NULL || hero == NULL) {
        return false;
    }

    if (!list->is_root) {
        printf("\n\nUsuwanie bohaterow mozna tylko wykonac na oryginalnej liscie.\n\n");
    }

    if (hero->status == ON_QUEST) {
        printf("Blad usuwania %s - Nie mozna wyrejestrowac bohatera, ktory jest na misji.\n", hero->name);
        return false;
    }

    for (int i = 0; i < list->count; i++) {
        if (list->heroes[i] == hero) {
            free(hero);

            for (int j = i; j < list->count - 1; j++) {
                list->heroes[j] = list->heroes[j + 1];
            }
            list->count--;
            return true;
        }
    }

    return true;
}

bool delete_heroes(HeroList* originalList, HeroList* subsetToDelete) {
    if (originalList == NULL || subsetToDelete == NULL) {
        return false;
    }

    HeroListIterator iterator = hero_iterator(subsetToDelete);
    while (has_next_hero(&iterator)) {
        Hero* heroToDelete = get_next_hero(&iterator);
        delete_hero(originalList, heroToDelete);
    }

    return true;
}

