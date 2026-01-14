#include "hero_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------------------------

HeroListIterator hero_iterator(HeroList* list) {
    HeroListIterator iterator = {list->head};
    return iterator;
}

bool has_next_hero(HeroListIterator* iterator) {
    return iterator->current_node != NULL;
}

Hero* get_next_hero(HeroListIterator* iterator) {
    if (!has_next_hero(iterator)) {
        return NULL;
    }
    Hero* hero = iterator->current_node->hero;
    iterator->current_node = iterator->current_node->next;
    return hero;
}

// -------------------------------------------------

HeroList* init_hero_list() {
    HeroList* list = (HeroList*)malloc(sizeof(HeroList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->count = 0;
    list->is_root = true;

    return list;
}

void free_hero_list(HeroList* list) {
    if (list != NULL) {
        HeroNode* current = list->head;
        while (current != NULL) {
            HeroNode* temp = current;
            current = current->next;
            
            if (list->is_root) {
                free(temp->hero);
            }
            free(temp);
        }
        free(list);
    }
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

    Hero* new_hero = malloc(sizeof(Hero));
    if (new_hero == NULL) {
        return NULL;
    }
    
    *new_hero = create_hero(name, race, hero_class, experience_level, reputation, status);
    
    HeroNode* new_node = malloc(sizeof(HeroNode));
    if (new_node == NULL) {
        free(new_hero);
        return NULL;
    }
    
    new_node->hero = new_hero;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        HeroNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    list->count++;
    return new_hero;
}

/**
 * Dodaje istniejacego bohatera do listy bez tworzenia nowego obiektu.
 * Uzywane przy tworzeniu podzbiorów głównej listy.
 */
Hero* add_hero_direct(HeroList* list, Hero* hero) {
    if (list == NULL || hero == NULL) {
        return NULL;
    }
    
    HeroNode* new_node = malloc(sizeof(HeroNode));
    if (new_node == NULL) {
        return NULL;
    }
    
    new_node->hero = hero;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        HeroNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    list->count++;
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

    for (HeroNode* i = list->head; i != NULL; i = i->next) {
        for (HeroNode* j = list->head; j->next != NULL; j = j->next) {
            if (!compare(j->hero, j->next->hero, state)) {
                // Swap hero pointers
                Hero* temp = j->hero;
                j->hero = j->next->hero;
                j->next->hero = temp;
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

    HeroListIterator iterator = hero_iterator(list);
    while (has_next_hero(&iterator)) {
        Hero* hero = get_next_hero(&iterator);
        add_hero_direct(sorted_list, hero);
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
        return false;
    }

    if (hero->status == ON_QUEST) {
        printf("Blad usuwania %s - Nie mozna wyrejestrowac bohatera, ktory jest na misji.\n", hero->name);
        return false;
    }

    if (list->head->hero == hero) {
        HeroNode* temp = list->head;
        list->head = list->head->next;
        free(hero);
        free(temp);
        list->count--;
        return true;
    }

    for (HeroNode* current = list->head; current->next != NULL; current = current->next) {
        if (current->next->hero == hero) {
            HeroNode* temp = current->next;
            current->next = current->next->next;
            free(hero);
            free(temp);
            list->count--;
            return true;
        }
    }

    return false;
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

