#include "hero_menu.h"
#include <stdio.h>
#include "../hero/hero_list.h"
#include "../io/text_input_handler.h"
#include "../util/list_utils.h"
#include "../io/file_handler.h"
#include <string.h>

const char* HERO_MENU_OPTIONS = "\n==== Zarzadzanie bohaterami: ====\n"
                                "1. Wyswietl obecna liste bohaterow. (%d)\n"
                                "2. Wyczysc filtry.\n"
                                "3. Wyszukaj bohaterow.\n"
                                "4. Sortuj bohaterow.\n"
                                "5. Edytuj bohaterow.\n"
                                "6. Usun bohaterow.\n"
                                "7. Zapisz wybor do pliku\n"
                                "\n"
                                "0. Wroc do glownego menu.\n"
                                "\n"
                                "Wybierz opcje: ";
const char* HERO_MENU_FIND_OPTIONS = "\n==== Filtruj bohaterow po: ====\n"
                                     "1. Imieniu (dopasowanie pelne).\n"
                                     "2. Imeniu (dopasowanie prefixowe).\n"
                                     "3. Powyzej poziomu doswiadczenia.\n"
                                     "4. Ponizej poziomu doswiadczenia.\n"
                                     "5. Powyzej reputacji.\n"
                                     "6. Ponizej reputacji.\n"
                                     "7. Rasie.\n"
                                     "8. Klasie.\n"
                                     "9. Statusie\n"
                                     "\n"
                                     "0. Anuluj.\n"
                                     "\n"
                                     "Wybierz opcje: ";

const char* HERO_MENU_SORT_OPTIONS = "\n==== Sortuj bohaterow po: ====\n"
                                     "1. Imieniu.\n"
                                     "2. Poziomie.\n"
                                     "3. Reputacji.\n"
                                     "4. Rasie.\n"
                                     "5. Klasie.\n"
                                     "6. Statusie.\n"
                                     "\n"
                                     "0. Anuluj.\n"
                                     "\n"
                                     "Wybierz opcje: ";

const char* HERO_EDIT_MENU_OPTIONS = "\n==== Edytuj: ====\n"
                                     "1. Poziom.\n"
                                     "2. Reputacje.\n"
                                     "3. Status. \n"
                                     "4. Klase.\n"
                                     "5. Rase.\n"
                                     "\n"
                                     "6. Przejdz do nastepnego bohatera w liscie.\n"
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
    HeroCompareFunc func;
    HeroCompareFunc functions[] = {NULL, compare_by_name, compare_by_level, compare_by_reputation, compare_by_race, compare_by_class, compare_by_status};
    bool ascending = true;
    int choice = read_integer_range(HERO_MENU_SORT_OPTIONS, 0, 6);
    func = functions[choice];
    if (func == NULL)
        return original_list;

    char buff[4];
    read_string("Sortuj rosnaco? (t/n): ", buff, 4);
    if (strcmp(buff, "nie") == 0 || strcmp(buff, "n") == 0 || strcmp(buff, "no") == 0) {
        ascending = false;
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

const char* print_menu_options(HeroList* list) {
    printf(HERO_MENU_OPTIONS, list->count);
    return NULL;
}

bool edit_hero_menu(Hero* hero) {
    int choice;

    do {
        print_hero(hero);
        choice = read_integer_range(HERO_EDIT_MENU_OPTIONS, 0, 6);
        switch (choice) {
            case 1:
                hero->experience_level = read_integer_range("Nowy poziom: ", 1, 100);
                break;
            case 2:
                hero->reputation = read_integer_range("Nowa reputacja: ", 1, 100);
                break;
            case 3:
                hero->status = pick_status();
                break;
            case 4:
                hero->hero_class = pick_class();
                break;
            case 5:
                hero->race = pick_race();
                break;
            case 6: 
                return true;
                break;
        }
    } while(choice != 0);

    return false;
}

void hero_menu(HeroList* hero_list, const char* output_file) {
    HeroList* current_list = hero_list;
    HeroList* temp_list;
    int choice;
    do {
        print_menu_options(current_list);
        choice = read_integer(NULL);

        switch (choice) {
            case 1:
                display_heroes(current_list);
                printf("\n");
                break;
            case 2:
                if (current_list != hero_list) {
                    free_hero_list(current_list);
                }
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
                HeroListIterator iterator = hero_iterator(current_list);
                bool exit = false;
                while (has_next_hero(&iterator) && !exit) {
                    exit = !edit_hero_menu(get_next_hero(&iterator));
                }
                break;
            case 6:
                if (hero_list == current_list || hero_list->count == current_list->count) {
                    printf("\n\nUwaga! Operujesz na calej liscie, nie podzbiorze..\n\n");
                }
                char buff[4];
                read_string("\nCzy napewno chcesz usunac wybranych bohaterow? (t/n): ", buff, 4);
                if (strcmp(buff, "tak") == 0 || strcmp(buff, "t") == 0 || strcmp(buff, "yes") == 0 || strcmp(buff, "y") == 0) {
                    delete_heroes(hero_list, current_list);
                    if (current_list != hero_list) {
                        free_hero_list(current_list);
                    }
                    current_list = hero_list;
                }
                break;
            case 7:
                char buffer[MAX_FILE_NAME_LENGTH+1];
                get_path_or_default("Podaj sciezke zapisu podzbioru (lub wcisnij enter dla domyslnej): ", output_file, buffer);
                if (save_list_to_file(current_list, buffer) != FILE_OK) {
                    printf("\n\nBlad zapisu do pliku.\n\n");
                } else {
                    printf("\n\nZapis dokonano pomyslnie.\n\n");
                }
                break;
            case 0:
                if (current_list != hero_list) {
                    free_hero_list(current_list);
                }
                break;
            default:
                printf("\n\nNieprawidlowy wybor. Sprobuj ponownie.\n");
        }
    } while (choice != 0);
}