#ifndef LIST_UTILS_H
#define LIST_UTILS_H

#include "../hero/hero.h"
#include "../hero/hero_list.h"

int pick_race();
int pick_class();
int pick_status();

// Filtry po nazwie
bool find_by_name_exact_filter(const Hero* hero, const void* state);
bool find_by_name_prefix_filter(const Hero* hero, const void* state);

// Filtry po poziomie doświadczenia
bool find_by_level_min(const Hero* hero, const void* state);
bool find_by_level_max(const Hero* hero, const void* state);

// Filtry po reputacji
bool find_by_reputation_min(const Hero* hero, const void* state);
bool find_by_reputation_max(const Hero* hero, const void* state);

// Filtry po rasie, klasie i statusie
bool find_by_race(const Hero* hero, const void* state);
bool find_by_class(const Hero* hero, const void* state);
bool find_by_status(const Hero* hero, const void* state);


bool compare_by_level(const Hero* a, const Hero* b, const void* state);
bool compare_by_reputation(const Hero* a, const Hero* b, const void* state);
bool compare_by_status(const Hero* a, const Hero* b, const void* state);
bool compare_by_name(const Hero* a, const Hero* b, const void* state);
bool compare_by_race(const Hero* a, const Hero* b, const void* state);
bool compare_by_class(const Hero* a, const Hero* b, const void* state);

#endif // LIST_UTILS_H