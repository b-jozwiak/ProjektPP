#include "main_menu.h"
#include <stdlib.h>
#include "../hero/hero_list.h"
#include <stdio.h>
#include "text_input_handler.h"
#include "../hero/hero.h"
#include "hero_menu.h"
#include <string.h>
#include "../util/list_utils.h"

const char* MENU_OPTIONS = "====== Rejestr Gildii Poszukiwaczy Przygod ======\n"
                           "1. Zarejestruj nowego bohatera.\n"
                           "2. Zarzadzaj bohaterami.\n"
                           "3. Wczytaj bohaterow z pliku.\n"
                           "4. Zapisz bohaterow do pliku.\n"
                           "0. Zamknij program.\n"
                           "\n"
                           "Wybierz opcje: ";


void register_new_hero(HeroList* hero_list) {
    char name[MAX_HERO_NAME_LENGTH+1];
    printf("==== Rejestracja nowego bohatera: ====\n");
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

void main_menu(HeroList* hero_list) {
    int choice;
    do {
        choice = read_integer(MENU_OPTIONS);

        switch (choice) {
            case 1:
                register_new_hero(hero_list);
                break;
            case 2:
                hero_menu(hero_list);
                break;
            case 3:
                printf("Funkcja wczytywania bohaterow z pliku jeszcze nie zaimplementowana.\n");
                break;
            case 4:
                printf("Funkcja zapisywania bohaterow do pliku jeszcze nie zaimplementowana.\n");
                break;
            case 0:
                break;
            default:
                printf("Nieprawidlowy wybor. Sprobuj ponownie.\n");
        }
    } while (choice != 0);

}