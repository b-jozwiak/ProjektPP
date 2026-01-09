#include "file_handler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "text_input_handler.h"

void get_path(const char* prompt, char* buffer) {

    do {
        read_string(prompt, buffer, MAX_FILE_NAME_LENGTH+1);
    } while(strlen(buffer) == 0 && printf("Nazwa pliku nie moze byc pusta."));
}

bool save_list_to_file(HeroList* list) {
    if (list == NULL) return false;

    char buffer[MAX_FILE_NAME_LENGTH + 1];
    FILE* file;
    do {
        get_path("Podaj nazwe pliku: ", buffer);
        file = fopen(buffer, "w");
    } while(file == NULL && printf("Blad otwierania pliku."));

    fprintf(file, "HERO_LIST %d\n", list->count);

    HeroListIterator it = hero_iterator(list);
    while (has_next_hero(&it)) {
        Hero* h = get_next_hero(&it);
        if (h == NULL) continue;

        fprintf(file, "%s;%d;%d;%d;%d;%d\n",
            h->name,
            h->race,
            h->hero_class,
            h->experience_level,
            h->reputation,
            h->status
        );
    }

    fclose(file);
    return true;
}

HeroList* load_list_from_file() {
    char buffer[MAX_FILE_NAME_LENGTH + 1];
    FILE* file;

    do {
        get_path("Podaj nazwe pliku do odczytu: ", buffer);
        file = fopen(buffer, "r");
    } while (file == NULL && printf("Blad otwierania pliku.\n"));

    char line[512];
    int expected_count = 0;

        if (!fgets(line, sizeof(line), file)) {
        printf("Blad odczytu naglowka.\n");
        fclose(file);
        return NULL;
    }

    if (sscanf(line, "HERO_LIST %d", &expected_count) != 1 || expected_count < 0) {
        printf("Nieprawidlowy format naglowka pliku.\n");
        fclose(file);
        return NULL;
    }

    HeroList* list = init_hero_list();
    if (!list) {
        fclose(file);
        return NULL;
    }

    char FORMAT[64];
    snprintf(FORMAT, sizeof(FORMAT), "%%%ds;%%d;%%d;%%d;%%d;%%d", MAX_HERO_NAME_LENGTH);
    for (int i = 0; i < expected_count; i++) {
        if (!fgets(line, sizeof(line), file)) {
            printf("Plik zakonczony przedwcześnie.\n");
            free_hero_list(list);
            fclose(file);
            return NULL;
        }

        char name[MAX_HERO_NAME_LENGTH + 1];
        int race, hero_class, level, reputation, status;

        // TODO: Znalezc sposob na unikniecie buffer overflow.
        if (sscanf(
                line,
                FORMAT,
                name,
                &race,
                &hero_class,
                &level,
                &reputation,
                &status
            ) != 6) {
            printf("Nieprawidlowy rekord w pliku:\n%s\n", line);
            printf("\n\n%s %d %d %d %d %d", name, race, hero_class, level, reputation, status);
            free_hero_list(list);
            fclose(file);
            return NULL;
        }

        if ((hero_class < 0 || hero_class > 5) || (race < 0 || race > 4) || (status < 0 || status > 4) || (reputation < 0 || reputation > 100) || (level < 1 || level > 100)) {
            printf("Nieprawidlowe dane bohatera: %s\n", name);
            free_hero_list(list);
            fclose(file);
            return NULL;
        }

        add_hero(
            list,
            name,
            (HeroRace)race,
            (HeroClass)hero_class,
            level,
            reputation,
            (HeroStatus)status
        );
    }

    fclose(file);
    return list;
}