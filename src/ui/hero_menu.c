#include "hero_menu.h"
#include <stdio.h>
#include "../hero/hero_list.h"
#include "text_input_handler.h"
#include "../util/list_utils.h"
#include <string.h>

const char* HERO_MENU_OPTIONS = "==== Zarzadzanie bohaterami: ====\n"
                                "1. Wyswietl obecna liste bohaterow.\n"
                                "2. Wyczysc filtry.\n"
                                "3. Wyszukaj bohaterow.\n"
                                "4. Sortuj bohaterow.\n"
                                "5. Usun bohaterow.\n"
                                "0. Wroc do glownego menu.\n"
                                "\n"
                                "Wybierz opcje: ";
const char* HERO_MENU_FIND_OPTIONS = "==== Filtruj bohaterow po: ====\n"
                                     "1. Imieniu (dopasowanie pelne).\n"
                                     "2. Imeniu (dopasowanie prefixowe).\n"
                                     "3. Powyzej poziomu poziomu doswiadczenia.\n"
                                     "4. Ponizej poziomu doswiadczenia.\n"
                                     "5. Powyzej reputacji.\n"
                                     "6. Ponizej reputacji.\n"
                                     "7. Rasie.\n"
                                     "8. Klasie.\n"
                                     "9. Statusie\n"
                                     "0. Anuluj.\n"
                                     "\n"
                                     "Wybierz opcje: ";



HeroList* menu_find_heroes(HeroList* original_list) {
    HeroFilterFunc func;
    const void* state;
    int choice = read_integer_range(HERO_MENU_FIND_OPTIONS, 0, 9);
    char name[MAX_HERO_NAME_LENGTH + 1];
    switch(choice) {
        case 0:
            break;
        case 1:
            func = find_by_name_exact_filter;
            read_string("Podaj imie: ", name, MAX_HERO_NAME_LENGTH + 1);
            state = name;
            break;
        case 2:
            func = find_by_name_prefix_filter;
            read_string("Podaj prefix: ", name, MAX_HERO_NAME_LENGTH + 1);
            state = name;
            break;
        case 3:
            break;
    }

    if (func == NULL)
        return original_list;
    return filter_heroes(original_list, func, state);
}

HeroList* menu_sort_heroes(HeroList* original_list) {
    printf("Work in progress!");
    return original_list;
}

void display_heroes(HeroList* list) {
    HeroListIterator iterator = hero_iterator(list);
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
                display_heroes(current_list);
                break;
            case 2:
                current_list = hero_list;
            case 3:
                current_list = menu_find_heroes(current_list);
                break;
            case 4:
                current_list = menu_sort_heroes(current_list);
                break;
            case 5:
                if (hero_list == current_list) {
                    printf("Blad! Nie dokonano wyboru bohaterow.");
                    break;
                }
                char buff[4];
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