#ifndef LIST_UTILS_H
#define LIST_UTILS_H

#include "../hero/hero.h"
#include "../hero/hero_list.h"

/**
 * Funkcja pozwalająca użytkownikowi wybrać rasę bohatera.
 * 
 * Wyświetla menu z dostępnymi rasami i wczytuje wybór użytkownika.
 * Funkcja zwraca indeks wybranej rasy (0-4).
 */
int pick_race();

/**
 * Funkcja pozwalająca użytkownikowi wybrać klasę/profesję bohatera.
 * 
 * Wyświetla menu z dostępnymi klasami i wczytuje wybór użytkownika.
 * Funkcja zwraca indeks wybranej klasy (0-5).
 */
int pick_class();

/**
 * Funkcja pozwalająca użytkownikowi wybrać status bohatera.
 * 
 * Wyświetla menu z dostępnymi statusami i wczytuje wybór użytkownika.
 * Funkcja zwraca indeks wybranego statusu (0-4).
 */
int pick_status();


/**
 * Funkcja filtrująca bohaterów po pełnym imieniu (dokładne dopasowanie).
 *
 * const Hero* hero - Bohater do sprawdzenia.
 * const void* state - Wskaźnik na const char* z szukane imię.
 * 
 * Funkcja zwraca true jeśli imię bohatera zgadza się dokładnie.
 */
bool find_by_name_exact_filter(const Hero* hero, const void* state);

/**
 * Funkcja filtrująca bohaterów po prefiksie imienia.
 *
 * const Hero* hero - Bohater do sprawdzenia.
 * const void* state - Wskaźnik na const char* z szukany prefiks.
 * 
 * Funkcja zwraca true jeśli imię bohatera zaczyna się od prefiksu.
 */
bool find_by_name_prefix_filter(const Hero* hero, const void* state);

/**
 * Funkcja filtrująca bohaterów z poziomem doświadczenia >= od podanego.
 *
 * const Hero* hero - Bohater do sprawdzenia.
 * const void* state - Wskaźnik na int z minimalnym poziomem.
 * 
 * Funkcja zwraca true jeśli hero->experience_level >= wartość.
 */
bool find_by_level_min(const Hero* hero, const void* state);

/**
 * Funkcja filtrująca bohaterów z poziomem doświadczenia <= od podanego.
 *
 * const Hero* hero - Bohater do sprawdzenia.
 * const void* state - Wskaźnik na int z maksymalnym poziomem.
 * 
 * Funkcja zwraca true jeśli hero->experience_level <= wartość.
 */
bool find_by_level_max(const Hero* hero, const void* state);

/**
 * Funkcja filtrująca bohaterów z reputacją >= od podanej.
 *
 * const Hero* hero - Bohater do sprawdzenia.
 * const void* state - Wskaźnik na int z minimalną reputacją.
 * 
 * Funkcja zwraca true jeśli hero->reputation >= wartość.
 */
bool find_by_reputation_min(const Hero* hero, const void* state);

/**
 * Funkcja filtrująca bohaterów z reputacją <= od podanej.
 *
 * const Hero* hero - Bohater do sprawdzenia.
 * const void* state - Wskaźnik na int z maksymalną reputacją.
 * 
 * Funkcja zwraca true jeśli hero->reputation <= wartość.
 */
bool find_by_reputation_max(const Hero* hero, const void* state);

/**
 * Funkcja filtrująca bohaterów po rasie.
 *
 * const Hero* hero - Bohater do sprawdzenia.
 * const void* state - Wskaźnik na HeroRace ze szukaną rasą.
 * 
 * Funkcja zwraca true jeśli hero->race == rasa.
 */
bool find_by_race(const Hero* hero, const void* state);

/**
 * Funkcja filtrująca bohaterów po klasie.
 *
 * const Hero* hero - Bohater do sprawdzenia.
 * const void* state - Wskaźnik na HeroClass ze szukaną klasą.
 * 
 * Funkcja zwraca true jeśli hero->hero_class == klasa.
 */
bool find_by_class(const Hero* hero, const void* state);

/**
 * Funkcja filtrująca bohaterów po statusie.
 *
 * const Hero* hero - Bohater do sprawdzenia.
 * const void* state - Wskaźnik na HeroStatus ze szukanym statusem.
 * 
 * Funkcja zwraca true jeśli hero->status == status.
 */
bool find_by_status(const Hero* hero, const void* state);



/**
 * Funkcja porównująca bohaterów po poziomie doświadczenia.
 *
 * const Hero* a - Pierwszy bohater.
 * const Hero* b - Drugi bohater.
 * const void* state - Wskaźnik na bool (ascending: true=rosnąco, false=malejąco).
 * 
 * Funkcja zwraca true jeśli a powinien być przed b.
 */
bool compare_by_level(const Hero* a, const Hero* b, const void* state);

/**
 * Funkcja porównująca bohaterów po reputacji.
 *
 * const Hero* a - Pierwszy bohater.
 * const Hero* b - Drugi bohater.
 * const void* state - Wskaźnik na bool (ascending: true=rosnąco, false=malejąco).
 * 
 * Funkcja zwraca true jeśli a powinien być przed b.
 */
bool compare_by_reputation(const Hero* a, const Hero* b, const void* state);

/**
 * Funkcja porównująca bohaterów po statusie.
 *
 * const Hero* a - Pierwszy bohater.
 * const Hero* b - Drugi bohater.
 * const void* state - Wskaźnik na bool (ascending: true=rosnąco, false=malejąco).
 * 
 * Funkcja zwraca true jeśli a powinien być przed b.
 */
bool compare_by_status(const Hero* a, const Hero* b, const void* state);

/**
 * Funkcja porównująca bohaterów alfabetycznie po imieniu.
 *
 * const Hero* a - Pierwszy bohater.
 * const Hero* b - Drugi bohater.
 * const void* state - Wskaźnik na bool (ascending: true=A-Z, false=Z-A).
 * 
 * Funkcja zwraca true jeśli a powinien być przed b.
 */
bool compare_by_name(const Hero* a, const Hero* b, const void* state);

/**
 * Funkcja porównująca bohaterów po rasie.
 *
 * const Hero* a - Pierwszy bohater.
 * const Hero* b - Drugi bohater.
 * const void* state - Wskaźnik na bool (ascending: true=rosnąco, false=malejąco).
 * 
 * Funkcja zwraca true jeśli a powinien być przed b.
 */
bool compare_by_race(const Hero* a, const Hero* b, const void* state);

/**
 * Funkcja porównująca bohaterów po klasie.
 *
 * const Hero* a - Pierwszy bohater.
 * const Hero* b - Drugi bohater.
 * const void* state - Wskaźnik na bool (ascending: true=rosnąco, false=malejąco).
 * 
 * Funkcja zwraca true jeśli a powinien być przed b.
 */
bool compare_by_class(const Hero* a, const Hero* b, const void* state);

#endif // LIST_UTILS_H