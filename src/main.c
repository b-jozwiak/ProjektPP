#include <stdio.h>
#include <stdlib.h>
#include "hero/hero.h"

int main() {
    HeroList* hero_list = init_hero_list();
    if (hero_list == NULL) {
        fprintf(stderr, "Blad tworzenia listy bohaterow.\n");
        return 1;
    }
    
    printf("Lista bohaterow z obecna pojemnoscia: %d\n", hero_list->capacity);

    free_hero_list(hero_list);
    return 0;
}