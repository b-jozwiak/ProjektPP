#include <stdio.h>
#include <stdlib.h>
#include "hero/hero.h"
#include "hero/hero_list.h"
#include <string.h>


bool find_by_name_filter(const Hero* hero, void* state) {
    const char* target_name = (const char*)state;
    return strcmp(hero->name, target_name) == 0;
}
bool find_by_min_level(const Hero* hero, void* state) {
    int min_level = *(int*)state;
    return hero->experience_level >= min_level;
}

bool compare_by_level(const Hero* a, const Hero* b, void* state) {
    bool reverse = (state != NULL) ? *(bool*)state : false;
    if (reverse) {
        return a->experience_level < b->experience_level;
    }
    return a->experience_level > b->experience_level;
}

int main() {
    HeroList* hero_list = init_hero_list();
    if (hero_list == NULL) {
        fprintf(stderr, "Blad tworzenia listy bohaterow.\n");
        return 1;
    }

    add_hero(hero_list, "Aragorn", HUMAN, WARRIOR, 15, 90, ACTIVE);
    add_hero(hero_list, "Gandalf", ELF, MAGE, 20, 95, ACTIVE);
    add_hero(hero_list, "Gimli", DWARF, WARRIOR, 12, 85, ON_QUEST);


    printf("\n=== Wszyscy bohaterowie ===\n");
    HeroListIterator iter = hero_iterator(hero_list);
    while (has_next_hero(&iter)) {
        Hero* h = get_next_hero(&iter);
        print_hero(h);
    }
    
    printf("\nLista zawiera: %d bohaterow\n", hero_list->count);

    int min_level = 15;
    HeroList* high_level_heroes = filter_heroes(hero_list, find_by_min_level, &min_level);
    if (high_level_heroes != NULL) {
        printf("\n=== Bohaterowie z poziomem doswiadczenia >= %d ===\n", min_level);
        HeroListIterator high_level_iter = hero_iterator(high_level_heroes);
        while (has_next_hero(&high_level_iter)) {
            Hero* h = get_next_hero(&high_level_iter);
            print_hero(h);
        }

        HeroList* sorted_heroes = sort_heroes(high_level_heroes, compare_by_level, NULL);
        if (sorted_heroes != NULL) {
            printf("\n=== Bohaterowie posortowani wedlug poziomu doswiadczenia ===\n");
            HeroListIterator sorted_iter = hero_iterator(sorted_heroes);
            while (has_next_hero(&sorted_iter)) {
                Hero* h = get_next_hero(&sorted_iter);
                print_hero(h);
            }
            free_hero_list(sorted_heroes);
        } else {
            printf("Blad sortowania bohaterow.\n");
        }
        free_hero_list(high_level_heroes);
    } else {
        printf("Brak bohaterow spelniajacych kryteria filtra.\n");
    }



    free_hero_list(hero_list);
    return 0;
}