#include "file_handler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "text_input_handler.h"

#define LINE_BUFFER_SIZE 512
#define FORMAT_BUFFER_SIZE 64

FileErrorCode file_exists(const char* file_path) {
    if (file_path == NULL) {
        return FILE_ERROR_INVALID_POINTER;
    }
    
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        return FILE_NOT_FOUND;
    }
    
    fclose(file);
    return FILE_OK;
}

FileErrorCode save_list_to_file(HeroList* list, const char* file_path) {
    if (list == NULL || file_path == NULL) {
        return FILE_ERROR_INVALID_POINTER;
    }

    FILE* file = fopen(file_path, "w");
    if (file == NULL) {
        printf("Blad: Nie mozna otworzyc pliku '%s' do zapisu.\n", file_path);
        return FILE_ERROR_OPEN;
    }

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
    return FILE_OK;
}

FileErrorCode load_list_from_file(const char* file_path, HeroList** out_list) {
    if (file_path == NULL || out_list == NULL) {
        return FILE_ERROR_INVALID_POINTER;
    }

    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        return FILE_NOT_FOUND;
    }

    char line[LINE_BUFFER_SIZE];
    int expected_count = 0;

    if (!fgets(line, sizeof(line), file)) {
        printf("Blad odczytu naglowka.\n");
        fclose(file);
        return FILE_ERROR_READ;
    }

    if (sscanf(line, "HERO_LIST %d", &expected_count) != 1 || expected_count < 0) {
        printf("Nieprawidlowy format naglowka pliku.\n");
        fclose(file);
        return FILE_ERROR_INVALID_HEADER;
    }

    HeroList* list = init_hero_list();
    if (!list) {
        fclose(file);
        return FILE_ERROR_READ;
    }

    char FORMAT[FORMAT_BUFFER_SIZE];
    snprintf(FORMAT, FORMAT_BUFFER_SIZE, "%%%d[^;];%%d;%%d;%%d;%%d;%%d", MAX_HERO_NAME_LENGTH);
    for (int i = 0; i < expected_count; i++) {
        if (!fgets(line, sizeof(line), file)) {
            printf("Plik zakonczony przedwcześnie.\n");
            free_hero_list(list);
            fclose(file);
            return FILE_ERROR_READ;
        }

        char name[MAX_HERO_NAME_LENGTH + 1];
        int race, hero_class, level, reputation, status;

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
            printf("Nieprawidlowy rekord w pliku (oczekiwano 6 pol).\n");
            free_hero_list(list);
            fclose(file);
            return FILE_ERROR_INVALID_DATA;
        }

        if ((hero_class < 0 || hero_class > 5) || (race < 0 || race > 4) || (status < 0 || status > 4) || (reputation < 0 || reputation > 100) || (level < 1 || level > 100)) {
            printf("Nieprawidlowe dane bohatera (Linia: %d): %s\n", i+2, name);
            free_hero_list(list);
            fclose(file);
            return FILE_ERROR_INVALID_DATA;
        }

        if (!is_name_avaliable(list, name)) {
            printf("Nieunikalne imie bohatera (Linia %d): %s\n", i+2, name);
            free_hero_list(list);
            fclose(file);
            return FILE_ERROR_INVALID_DATA;
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
    *out_list = list;
    return FILE_OK;
}

int is_path_valid(const char* path) {
    if (path == NULL || strlen(path) == 0) {
        return 0;
    }

    int is_whitespace_only = 1;
    for (int i = 0; path[i] != '\0'; i++) {
        if (path[i] != ' ' && path[i] != '\t' && path[i] != '\n' && path[i] != '\r') {
            is_whitespace_only = 0;
            break;
        }
    }

    if (is_whitespace_only) {
        return 0;
    }

    const char* forbidden = "<>:\"|?*";
    for (int i = 0; path[i] != '\0'; i++) {
        for (int j = 0; forbidden[j] != '\0'; j++) {
            if (path[i] == forbidden[j]) {
                printf("Blad: Sciezka zawiera niedozwolony znak '%c'.\n", path[i]);
                return 0;
            }
        }
    }

    return 1;
}

void trim_path(char* str) {
    if (str == NULL) return;

    int start = 0;
    while (str[start] != '\0' && (str[start] == ' ' || str[start] == '\t')) {
        start++;
    }

    int end = strlen(str) - 1;
    while (end >= start && (str[end] == ' ' || str[end] == '\t')) {
        end--;
    }

    int j = 0;
    for (int i = start; i <= end; i++) {
        str[j++] = str[i];
    }
    str[j] = '\0';
}

FileErrorCode get_path_or_default(const char* prompt, const char* default_path, char* output) {
    if (prompt == NULL || default_path == NULL || output == NULL) {
        return FILE_ERROR_INVALID_POINTER;
    }

    char buffer[MAX_FILE_NAME_LENGTH + 1];
    read_string(prompt, buffer, MAX_FILE_NAME_LENGTH + 1);

    trim_path(buffer);

    const char* path_to_use = (strlen(buffer) == 0) ? default_path : buffer;

    if (!is_path_valid(path_to_use)) {
        printf("Blad: Nieprawidlowa sciezka do pliku.\n");
        return FILE_ERROR_OPEN;
    }

    strncpy(output, path_to_use, MAX_FILE_NAME_LENGTH);
    output[MAX_FILE_NAME_LENGTH] = '\0';

    return FILE_OK;
}