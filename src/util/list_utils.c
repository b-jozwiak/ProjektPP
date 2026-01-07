#include "list_utils.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool find_by_name_filter(const Hero* hero, void* state) {
    const char* target_name = (const char*)state;
    return strcmp(hero->name, target_name) == 0;
}

bool find_by_min_level(const Hero* hero, void* state) {
    int min_level = *(int*)state;
    return hero->experience_level >= min_level;
}

bool compare_by_level(const Hero* a, const Hero* b, void* state) {
    bool reverse = (state != NULL) ? *(bool*)state : false;
    if (reverse) {
        return a->experience_level < b->experience_level;
    }
    return a->experience_level > b->experience_level;
}