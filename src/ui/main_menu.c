#include "main_menu.h"
#include <stdlib.h>
#include "../hero/hero_list.h"
#include <stdio.h>
#include "../io/text_input_handler.h"
#include "../io/file_handler.h"
#include "../hero/hero.h"
#include "hero_menu.h"
#include <string.h>
#include "../util/list_utils.h"

const char* MENU_OPTIONS = "====== Rejestr Gildii Poszukiwaczy Przygod ======\n"
                           "1. Zarejestruj nowego bohatera.\n"
                           "2. Zarzadzaj bohaterami.\n"
                           "3. Wczytaj bohaterow z pliku.\n"
                           "4. Zapisz bohaterow do pliku.\n"
                           "\n"
                           "0. Zamknij program.\n"
                           "\n"
                           "Wybierz opcje: ";


void register_new_hero(HeroList* hero_list) {
    char name[MAX_HERO_NAME_LENGTH+1];
    printf("\n==== Rejestracja nowego bohatera: ====\n\n");
    do {
    read_string("Podaj imie bohatera: ", name, MAX_HERO_NAME_LENGTH + 1);
    } while (!is_name_avaliable(hero_list, name) && strlen(name) > 0 && printf("Imie jest juz zajete lub nieprawidlowe. Sprobuj ponownie.\n"));

    int race = pick_race();
    int class = pick_class();
    int experience = read_integer_range("Podaj poziom doswiadczenia (min 1): ", 1, 100);
    int reputation = read_integer_range("Podaj reputacje (0-100): ", 0, 100);
    add_hero(hero_list, name, race, class, experience, reputation, ACTIVE);
    printf("Bohater %s zostal pomyslnie zarejestrowany.\n", name);
}

void main_menu(HeroList** list_ptr) {
    int choice;
    do {
        HeroList* hero_list = *list_ptr;
        choice = read_integer(MENU_OPTIONS);

        switch (choice) {
            case 1:
                register_new_hero(hero_list);
                break;
            case 2:
                hero_menu(hero_list);
                break;
            case 3:
                HeroList* old_list = hero_list;
                HeroList* new_list = load_list_from_file();
                if (new_list != old_list && new_list != NULL) {
                    *list_ptr = new_list;
                    free_hero_list(old_list);
                } else {
                    printf("\n\nBlad wczytu z pliku.\n\n");
                }
                break;
            case 4:
                if (!save_list_to_file(hero_list)) {
                    printf("\n\nBlad zapisu do pliku.\n\n");
                }
                break;
            case 0:
                break;
            default:
                printf("\n\nNieprawidlowy wybor. Sprobuj ponownie.\n\n");
        }
    } while (choice != 0);

}