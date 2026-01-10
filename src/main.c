#include <stdio.h>
#include <stdlib.h>
#include "hero/hero.h"
#include "hero/hero_list.h"
#include "util/list_utils.h"
#include "ui/main_menu.h"
#include "io/file_handler.h"
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

    // Spróbuj automatycznie załadować plik przy starcie
    if (file_exists(data_file) == FILE_OK) {
        HeroList* loaded_list = NULL;
        FileErrorCode err = load_list_from_file(data_file, &loaded_list);
        if (err == FILE_OK && loaded_list != NULL) {
            free_hero_list(hero_list);
            hero_list = loaded_list;
            printf("Lista bohaterow zostala zaladowana z pliku '%s'.\n\n", data_file);
        } else {
            printf("Uwaga: Nie mozna zaladowac listy z pliku '%s'. Zaczynamy z pusta lista.\n\n", data_file);
        }
    } else {
        printf("Plik '%s' nie istnieje. Zaczynamy z pusta lista.\n\n", data_file);
    }

    main_menu(&hero_list, data_file, output_file);

    free_hero_list(hero_list);
    return 0;
}