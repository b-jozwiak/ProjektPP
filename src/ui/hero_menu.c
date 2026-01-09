#include "hero_menu.h"
#include <stdio.h>
#include "../hero/hero_list.h"
#include "text_input_handler.h"

const char* HERO_MENU_OPTIONS = "==== Zarzadzanie bohaterami: ====\n"
                                "1. Wyswietl obecna liste bohaterow.\n"
                                "2. Wyszukaj bohaterow.\n"
                                "3. Sortuj bohaterow.\n"
                                "4. Usun bohaterow.\n"
                                "0. Wroc do glownego menu.\n"
                                "\n"
                                "Wybierz opcje: ";

HeroList* menu_find_heroes(HeroList* original_list) {
    printf("Work in progress!");
    return original_list;
}

HeroList* menu_sort_heroes(HeroList* original_list) {
    printf("Work in progress!");
    return original_list;
}

void display_heroes(HeroList* list) {
    HeroListIterator iterator = hero_iterator(current_list);
    printf("==== Lista zarejestrowanych bohaterow: ====\n");
    while (has_next_hero(&iterator)) {
        Hero* hero = get_next_hero(&iterator);
        print_hero(hero);
    }
}


void hero_menu(HeroList* hero_list) {
    HeroList* current_list = hero_list;
    int choice;
    do {
        choice = read_integer(HERO_MENU_OPTIONS);

        switch (choice) {
            case 1:
                display_heroes(current_list)
                break;
            case 2:
                current_list = menu_find_heroes(current_list);
                break;
            case 3:
                current_list = menu_sort_heroes(current_list);
                break;
            case 4:
                if (hero_list == current_list) {
                    printf("Blad! Nie dokonano wyboru bohaterow.");
                    break;
                }
                char* buff = char[4];
                read_string("Czy napewno chcesz usunac wybranych bohaterow? (t/n)", buff, 4);
                if (strcmp(buff, "tak") || strcmp(buff, "t") || strcmp(buff, "yes") || strcmp(buff, "y")) {
                    delete_heroes(hero_list, current_list);
                    current_list = hero_list;
                }
                break;
            case 0:
                break;
            default:
                printf("Nieprawidlowy wybor. Sprobuj ponownie.\n");
        }
    } while (choice != 0);
}