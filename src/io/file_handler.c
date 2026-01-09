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