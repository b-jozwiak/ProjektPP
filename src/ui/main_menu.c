#include "main_menu.h"
#include <stdlib.h>
#include "../hero/hero_list.h"
#include <stdio.h>

const char* MENU_OPTIONS = "====== Rejestr Gildii Poszukiwaczy Przygod ======\n"
                           "1. Zarejestruj nowego bohatera.\n"
                           "2. Zarzadzaj rejestrem...\n"
                           "3. Wczytaj bohaterow z pliku.\n"
                           "4. Zapisz bohaterow do pliku.\n"
                           "0. Zamknij program.\n"
                           "\n"
                           "Wybierz opcje: ";


void register_new_hero(HeroList* hero_list) {
    printf("Funkcja rejestracji nowego bohatera jeszcze nie zaimplementowana.\n");
}

void main_menu(HeroList* hero_list) {
    int choice;
    do {
        printf("%s", MENU_OPTIONS);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_new_hero(hero_list);
                break;
            case 2:
                printf("Funkcja wyszukiwania bohaterow jeszcze nie zaimplementowana.\n");
                break;
            case 3:
                printf("Funkcja wczytywania bohaterow z pliku jeszcze nie zaimplementowana.\n");
                break;
        }
    } while (choice != 0);
}