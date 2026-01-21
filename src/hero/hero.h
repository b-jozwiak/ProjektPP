#ifndef HERO_H
#define HERO_H

/** Maksymalna ilość znaków w imieniu bohatera (terminator null nie jest wliczany). */
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
    ON_QUEST,   // (nie można usunąć bohatera w tym stanie)
    INJURED,
    MISSING,
    SUSPENDED
} HeroStatus;

/**
 * Struktura reprezentująca bohatera.
 * Zawiera podstawowe informacje o członku gildii.
 */
typedef struct {
    char name[MAX_HERO_NAME_LENGTH + 1];  // Unikalne imię (niezmienne po dodaniu)
    HeroRace race;                         // Rasa bohatera
    HeroClass hero_class;                  // Klasa/profesja
    int experience_level;                  // Poziom doświadczenia (1-100)
    int reputation;                        // Reputacja w gildii (0-100)
    HeroStatus status;                     // Status dostępności
} Hero;

/**
 * Funkcja tworząca bohatera
 *
 * const char* name - Imie bohatera, maksymalna długość 50 znaków + terminator (51 byteów)
 * HeroRace race - rasa bohatera
 * HeroClass hero_class - klasa bohatera
 * int experience_level - wartość w zakresie < 1 : 100 >
 * int reputation - wartość w zakresie < 0 ; 100 >
 * HeroStatus status - status bohatera
 */
Hero* create_hero(const char* name, HeroRace race, HeroClass hero_class, int experience_level, int reputation, HeroStatus status);

/**
 * Funkcja uwalnia pamięć danego bohatera.
 *
 * - na razie ekwialentne do pisania free(hero).
 * Przyszłościowo może się zmienić struktura bohatera.
 */
void free_hero(Hero* hero);

/**
 * Funkcja wyświetlająca informacje o bohaterze.
 *
 * const Hero* hero - Wskaźnik do struktury bohatera do wyświetlenia.
 * 
 * Funkcja nic nie zwraca. Wypisuje sformatowane informacje na standardowe wyjscie.
 */
void print_hero(const Hero* hero);

#endif // HERO_H
