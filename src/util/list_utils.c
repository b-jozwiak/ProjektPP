#include "list_utils.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../ui/text_input_handler.h"

int pick_race() {
    return read_integer_range("Wybierz rase (0-Czlowiek, 1-Elf, 2-Krasnolud, 3-Ork, 4-Tiefling): ", 0, 4);
}

int pick_class() {
    return read_integer_range("Wybierz klase (0-Wojownik, 1-Mag, 2-Kaplan, 3-Lotrzyk, 4-Lowca, 5-Druid): ", 0, 5);
}

int pick_status() {
    return read_integer_range("Wybierz status: (0-Aktywny, 1-Na miscji, 2-Ranny, 3-Zaginiony, 4-Zawieszony): ", 0, 4);
}

bool find_by_name_exact_filter(const Hero* hero, const void* state) {
    const char* target_name = (const char*)state;
        if (target_name == NULL || strlen(target_name) == 0) {
        printf("Brak imienia do przefiltrowania.");
        return true;
    }
    return strcmp(hero->name, target_name) == 0;
}

bool find_by_name_prefix_filter(const Hero* hero, const void* state) {
    const char* prefix = (const char*)state;
    int length;
    if (prefix == NULL || (length = strlen(prefix)) == 0) {
        printf("Brak prefixu do przefiltrowania.");
        return true;
    }
    
    return strncmp(hero->name, prefix, length) == 0;
}

bool find_by_level_min(const Hero* hero, const void* state) {
    if (state == NULL) return true;
    int min_level = *(int*)state;
    return hero->experience_level >= min_level;
}
bool find_by_level_max(const Hero* hero, const void* state) {
    if (state == NULL) return true;
    int max_level = *(int*)state;
    return hero->experience_level <= max_level;
}

bool find_by_reputation_min(const Hero* hero, const void* state) {
    if (state == NULL) return true;
    int min_reputation = *(int*)state;
    return hero->reputation >= min_reputation;
}
bool find_by_reputation_max(const Hero* hero, const void* state) {
    if (state == NULL) return true;
    int max_reputation = *(int*)state;
    return hero->reputation <= max_reputation;
}

bool find_by_race(const Hero* hero, const void* state) {
    if (state == NULL) return true;
    HeroRace race = *(HeroRace*)state;
    return hero->race == race;
}
bool find_by_class(const Hero* hero, const void* state) {
    if (state == NULL) return true;
    HeroClass class = *(HeroClass*)state;
    return hero->hero_class == class;
}

bool find_by_status(const Hero* hero, const void* state) {
    if (state == NULL) return true;
    HeroStatus status = *(HeroStatus*)state;
    return hero->status == status;
}

bool compare_by_level(const Hero* a, const Hero* b, const void* state) {
    bool reverse = (state != NULL) ? *(bool*)state : false;
    if (reverse) {
        return a->experience_level < b->experience_level;
    }
    return a->experience_level > b->experience_level;
}