#include "hero_menu.h"
#include <stdio.h>
#include "../hero/hero_list.h"
#include "text_input_handler.h"

const char* HERO_MENU_OPTIONS = "==== Zarzadzanie bohaterami: ====\n"
                                "1. Wyswietl liste bohaterow.\n"
                                "2. Wyszukaj bohatera.\n"
                                "3. Usun bohatera.\n"
                                "0. Wroc do glownego menu.\n"
                                "\n"
                                "Wybierz opcje: ";


void hero_menu(HeroList* hero_list) {
    HeroList* current_list = hero_list;
    int choice;
    do {
        choice = read_integer(HERO_MENU_OPTIONS);

        switch (choice) {
            case 1:
                HeroListIterator iterator = hero_iterator(current_list);
                printf("==== Lista zarejestrowanych bohaterow: ====\n");
                while (has_next_hero(&iterator)) {
                    Hero* hero = get_next_hero(&iterator);
                    print_hero(hero);
                }
                break;
            case 2:
                printf("Funkcja wyszukiwania bohaterow jeszcze nie zaimplementowana.\n");
                break;
            case 3:
                printf("Funkcja usuwania bohaterow jeszcze nie zaimplementowana.\n");
                break;
            case 0:
                break;
            default:
                printf("Nieprawidlowy wybor. Sprobuj ponownie.\n");
        }
    } while (choice != 0);
}