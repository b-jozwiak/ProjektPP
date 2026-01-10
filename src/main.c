#include <stdio.h>
#include <stdlib.h>
#include "hero/hero.h"
#include "hero/hero_list.h"
#include "util/list_utils.h"
#include "ui/main_menu.h"
#include <string.h>


int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        if (argc > 3) {
            fprintf(stderr, "Zbyt duzo argumentow.\n\n");
        }
        fprintf(stderr, "Uzycie: %s <plik_danych> [plik_zapisu]\n", argv[0]);
        fprintf(stderr, "Przyklad 1: %s bohaterowie.txt\n", argv[0]);
        fprintf(stderr, "Przyklad 2: %s wczytaj.txt zapisz.txt\n\n", argv[0]);
        fprintf(stderr, "Jezeli zostanie podany tylko jeden plik, bedzie on sluzyl jako plik wczytu i zapisu\n");
        return 1;
    }

    const char* data_file = argv[1];
    const char* output_file = argc > 2 ? argv[2] : data_file;


    HeroList* hero_list = init_hero_list();
    if (hero_list == NULL) {
        fprintf(stderr, "Blad tworzenia listy bohaterow.\n");
        return 1;
    }

    // add_hero(hero_list, "Ksiadz Nathan", HUMAN, PRIEST, 40, 10, ACTIVE);
    // add_hero(hero_list, "Adam Mickiewicz", HUMAN, DRUID, 10, 60, ACTIVE);
    // add_hero(hero_list, "Orgalorg", ORC, WARRIOR, 80, 99, ON_QUEST);

    main_menu(&hero_list, data_file, output_file);


    free_hero_list(hero_list);
    return 0;
}