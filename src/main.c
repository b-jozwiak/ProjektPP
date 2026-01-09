#include <stdio.h>
#include <stdlib.h>
#include "hero/hero.h"
#include "hero/hero_list.h"
#include "util/list_utils.h"
#include "ui/main_menu.h"
#include <string.h>


int main() {
    HeroList* hero_list = init_hero_list();
    if (hero_list == NULL) {
        fprintf(stderr, "Blad tworzenia listy bohaterow.\n");
        return 1;
    }

    add_hero(hero_list, "Ksiadz Nathan", HUMAN, PRIEST, 40, 10, ACTIVE);
    add_hero(hero_list, "Adam Mickiewicz", HUMAN, DRUID, 10, 60, ACTIVE);
    add_hero(hero_list, "Orgalorg", ORC, WARRIOR, 80, 99, ON_QUEST);

    main_menu(hero_list);


    free_hero_list(hero_list);
    return 0;
}