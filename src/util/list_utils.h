#ifndef LIST_UTILS_H
#define LIST_UTILS_H

#include "../hero/hero.h"
#include "../hero/hero_list.h"

bool find_by_name_filter(const Hero* hero, void* state);

bool find_by_min_level(const Hero* hero, void* state);

bool compare_by_level(const Hero* a, const Hero* b, void* state);

#endif // LIST_UTILS_H