#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../hero/hero_list.h"

#define MAX_FILE_NAME_LENGTH 256

/**
 * Funkcja zapisująca listę bohaterów do pliku tekstowego.
 *
 * HeroList* list - Wskaźnik do listy bohaterów do zapisania.
 * const char* file_path - Ścieżka do docelowego pliku.
 * 
 * Format pliku:
 *   HERO_LIST N
 *   name;race;class;level;reputation;status
 *   ...
 * 
 * Funkcja zwraca true jeśli zapis powiódł się, false w przypadku błędu.
 */
bool save_list_to_file(HeroList* list, const char* file_path);

/**
 * Funkcja wczytująca listę bohaterów z pliku tekstowego.
 *
 * const char* file_path - Ścieżka do pliku źródłowego.
 * 
 * Waliduje:
 *   - Format nagłówka (HERO_LIST N)
 *   - Poprawność enumeracji (race, class, status)
 *   - Zakresy wartości (level 1-100, reputation 0-100)
 *   - Kompletność danych (6 pól na bohatera)
 * 
 * Funkcja zwraca wskaźnik do nowej listy bohaterów, lub NULL jeśli błąd.
 */
HeroList* load_list_from_file(const char* file_path);

#endif // FILE_HANDLER_H