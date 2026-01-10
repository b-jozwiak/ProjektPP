#include "hero.h"
#include "hero_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_hero_class(HeroClass hero_class) {
    switch (hero_class) {
        case WARRIOR:
            printf("Wojownik");
            break;
        case MAGE:
            printf("Mag");
            break;
        case PRIEST:
            printf("Kaplan");
            break;
        case ROGUE:
            printf("Lotrzyk");
            break;
        case HUNTER:
            printf("Lowca");
            break;
        case DRUID:
            printf("Druid");
            break;
        default:
            printf("Nieznana klasa");
    }
}

void print_hero_race(HeroRace race) {
    switch (race) {
        case HUMAN:
            printf("Czlowiek");
            break;
        case ELF:
            printf("Elf");
            break;
        case DWARF:
            printf("Krasnolud");
            break;
        case ORC:
            printf("Ork");
            break;
        case TIEFLING:
            printf("Tiefling");
            break;
        default:
            printf("Nieznana rasa");
    }
}

void print_hero_status(HeroStatus status) {
    switch (status) {
        case ACTIVE:
            printf("Aktywny");
            break;
        case ON_QUEST:
            printf("Na misji");
            break;
        case INJURED:
            printf("Ranny");
            break;
        case MISSING:
            printf("Zaginionyy");
            break;
        case SUSPENDED:
            printf("Zawieszony");
            break;
        default:
            printf("Nieznany status");
    }
}

void print_hero(const Hero* hero) {
    if (hero == NULL) {
        fprintf(stderr, "Blad: Wskaznik na bohatera jest NULL.\n");
        return;
    }
    
    printf("\n=== Bohater ===\n");
    printf("Imie: %s\n", hero->name);
    printf("Rasa: ");
    print_hero_race(hero->race);
    printf("\n");
    printf("Klasa: ");
    print_hero_class(hero->hero_class);
    printf("\n");
    printf("Poziom doswiadczenia: %d\n", hero->experience_level);
    printf("Reputacja: %d/100\n", hero->reputation);
    printf("Status: ");
    print_hero_status(hero->status);
    printf("\n");
}
