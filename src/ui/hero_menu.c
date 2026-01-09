#include "hero_menu.h"
#include <stdio.h>
#include "../hero/hero_list.h"
#include "../io/text_input_handler.h"
#include "../util/list_utils.h"
#include "../io/file_handler.h"
#include <string.h>

const char* HERO_MENU_OPTIONS = "==== Zarzadzanie bohaterami: ====\n"
                                "1. Wyswietl obecna liste bohaterow.\n"
                                "2. Wyczysc filtry.\n"
                                "3. Wyszukaj bohaterow.\n"
                                "4. Sortuj bohaterow.\n"
                                "5. Edytuj bohaterow.\n"
                                "6. Usun bohaterow.\n"
                                "7. Zapisz wybor do pliku\n"
                                "0. Wroc do glownego menu.\n"
                                "\n"
                                "Wybierz opcje: ";
const char* HERO_MENU_FIND_OPTIONS = "==== Filtruj bohaterow po: ====\n"
                                     "1. Imieniu (dopasowanie pelne).\n"
                                     "2. Imeniu (dopasowanie prefixowe).\n"
                                     "3. Powyzej poziomu doswiadczenia.\n"
                                     "4. Ponizej poziomu doswiadczenia.\n"
                                     "5. Powyzej reputacji.\n"
                                     "6. Ponizej reputacji.\n"
                                     "7. Rasie.\n"
                                     "8. Klasie.\n"
                                     "9. Statusie\n"
                                     "0. Anuluj.\n"
                                     "\n"
                                     "Wybierz opcje: ";

const char* HERO_MENU_SORT_OPTIONS = "==== Sortuj bohaterow po: ====\n"
                                     "1. Imieniu.\n"
                                     "2. Poziomie.\n"
                                     "3. Reputacji.\n"
                                     "4. Rasie.\n"
                                     "5. Klasie.\n"
                                     "6. Statusie.\n"
                                     "0. Anuluj.\n"
                                     "\n"
                                     "Wybierz opcje: ";


HeroList* menu_find_heroes(HeroList* original_list) {
    HeroFilterFunc func;
    const void* state;
    int choice = read_integer_range(HERO_MENU_FIND_OPTIONS, 0, 9);
    char name[MAX_HERO_NAME_LENGTH + 1];
    int int_value = 0;
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
            func = find_by_level_min;
            int_value = read_integer_range("Poziom >= ", 1, 100);
            state = &int_value;
            break;
        case 4:
            func = find_by_level_max;
            int_value = read_integer_range("Poziom <= ", 1, 100);
            state = &int_value;
            break;
        case 5:
            func = find_by_reputation_min;
            int_value = read_integer_range("Reputacja >= ", 1, 100);
            state = &int_value;
            break;
        case 6:
            func = find_by_level_max;
            int_value = read_integer_range("Reputacja <= ", 1, 100);
            state = &int_value;
            break;
        case 7:
            func = find_by_race;
            int_value = pick_race();
            state = &int_value;
            break;
        case 8:
            func = find_by_class;
            int_value = pick_class();
            state = &int_value;
            break;
        case 9:
            func = find_by_status;
            int_value = pick_status();
            state = &int_value;
            break;
    }

    if (func == NULL)
        return original_list;
    return filter_heroes(original_list, func, state);
}

HeroList* menu_sort_heroes(HeroList* original_list) {
    printf("Work in progress!");

    HeroCompareFunc func;
    HeroCompareFunc functions[] = {NULL, compare_by_name, compare_by_level, compare_by_reputation, compare_by_race, compare_by_class, compare_by_status};
    bool ascending = false;
    int choice = read_integer_range(HERO_MENU_SORT_OPTIONS, 0, 6);
    func = functions[choice];
    if (func == NULL)
        return original_list;

    char buff[4];
    read_string("Sortuj rosnaco? (t/n): ", buff, 4);
    if (strcmp(buff, "nie") == 0 || strcmp(buff, "n") == 0 || strcmp(buff, "no") == 0) {
        ascending = true;
    }
    
    // sort_heroes_in_place(original_list, func, &ascending);
    // return original_list;
    return sort_heroes(original_list, func, &ascending);    
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
    HeroList* temp_list;
    int choice;
    do {
        choice = read_integer(HERO_MENU_OPTIONS);

        switch (choice) {
            case 1:
                display_heroes(current_list);
                break;
            case 2:
                current_list = hero_list;
                break;
            case 3:
                temp_list = menu_find_heroes(current_list);
                if (current_list != hero_list)
                    free_hero_list(current_list);
                current_list = temp_list;
                break;
            case 4:
                temp_list = menu_sort_heroes(current_list);
                if (current_list != hero_list)
                    free_hero_list(current_list);
                current_list = temp_list;
                break;
            case 5:
                printf("Funkcja niezaimplementowana");
                break;
            case 6:
                if (hero_list == current_list) {
                    printf("Blad! Nie dokonano wyboru bohaterow.");
                    break;
                }
                char buff[4];
                read_string("Czy napewno chcesz usunac wybranych bohaterow? (t/n)", buff, 4);
                if (strcmp(buff, "tak") == 0 || strcmp(buff, "t") == 0 || strcmp(buff, "yes") == 0 || strcmp(buff, "y") == 0) {
                    delete_heroes(hero_list, current_list);
                    current_list = hero_list;
                }
                break;
            case 7:
                if (!save_list_to_file(current_list)) {
                    printf("Blad zapisu do pliku.");
                }
                break;
            case 0:
                break;
            default:
                printf("Nieprawidlowy wybor. Sprobuj ponownie.\n");
        }
    } while (choice != 0);
}