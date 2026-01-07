#include <stdio.h>
#include <stdlib.h>
#include "hero/hero.h"

int main() {
    HeroList* hero_list = init_hero_list();
    if (hero_list == NULL) {
        fprintf(stderr, "Blad tworzenia listy bohaterow.\n");
        return 1;
    }

    add_hero(hero_list, "Aragorn", HUMAN, WARRIOR, 15, 90, ACTIVE);
    Hero* hero2 = add_hero(hero_list, "Gandalf", ELF, MAGE, 20, 95, ACTIVE);
    Hero* hero3 = add_hero(hero_list, "Gimli", DWARF, WARRIOR, 12, 85, ON_QUEST);


    printf("\n=== Wszyscy bohaterowie ===\n");
    HeroListIterator iter = hero_iterator(hero_list);
    while (has_next_hero(&iter)) {
        Hero* h = get_next_hero(&iter);
        print_hero(h);
    }
    
    printf("\nLista zawiera: %d bohaterow\n", hero_list->count);

    printf("\nUsuwanie bohatera: %s\n", hero2->name);
    if (!delete_hero(hero_list, hero2)) {
        printf("Nie mozna usunac bohatera %s.\n", hero2->name);
    }
    printf("\n=== Po usunieciu Gandalfa ===\n");

    iter = hero_iterator(hero_list);
    while (has_next_hero(&iter)) {
        Hero* h = get_next_hero(&iter);
        print_hero(h);
    }
    
    printf("\nLista zawiera: %d bohaterow\n", hero_list->count);

    free_hero_list(hero_list);
    return 0;
}