#ifndef HERO_H
#define HERO_H

// Ilość znaków w imieniu bohatera. Terminator null nie jest wliczany.
#define MAX_HERO_NAME_LENGTH 50

typedef enum {
    WARRIOR,
    MAGE,
    PRIEST,
    ROGUE,
    HUNTER,
    DRUID
} HeroClass;

typedef enum {
    HUMAN,
    ELF,
    DWARF,
    ORC,
    TIEFLING
} HeroRace;

typedef enum {
    ACTIVE,
    ON_QUEST,
    INJURED,
    MISSING,
    SUSPENDED
} HeroStatus;

typedef struct {
    char name[MAX_HERO_NAME_LENGTH + 1];
    HeroRace race;
    HeroClass hero_class;
    int experience_level;
    int reputation;
    HeroStatus status;
} Hero;

typedef struct {
    Hero *heroes;
    int count;
    int capacity;
    int next_id;
} HeroList;


HeroList* init_hero_list();
void resize_hero_list_if_needed(HeroList* list);
void free_hero_list(HeroList* list);

#endif // HERO_H