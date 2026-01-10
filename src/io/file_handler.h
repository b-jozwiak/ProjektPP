#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../hero/hero_list.h"

#define MAX_FILE_NAME_LENGTH 256

/**
 * Kody błędów dla operacji na plikach.
 */
typedef enum {
    FILE_OK = 0,                    // Operacja powiodła się
    FILE_ERROR_INVALID_POINTER = 1, // Przekazano NULL
    FILE_ERROR_OPEN = 2,            // Nie można otworzyć pliku
    FILE_ERROR_READ = 3,            // Błąd przy odczycie
    FILE_ERROR_INVALID_HEADER = 4,  // Zły nagłówek "HERO_LIST N"
    FILE_ERROR_INVALID_DATA = 5,    // Nieprawidłowe dane bohatera
    FILE_NOT_FOUND = 6              // Plik nie istnieje
} FileErrorCode;

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
 * Funkcja zwraca kod błędu (FILE_OK = sukces, inne = błąd).
 */
FileErrorCode save_list_to_file(HeroList* list, const char* file_path);

/**
 * Funkcja wczytująca listę bohaterów z pliku tekstowego.
 *
 * const char* file_path - Ścieżka do pliku źródłowego.
 * HeroList** out_list - Wskaźnik do wskaźnika, gdzie umieścić wczytaną listę.
 * 
 * Waliduje:
 *   - Format nagłówka (HERO_LIST N)
 *   - Poprawność enumeracji (race, class, status)
 *   - Zakresy wartości (level 1-100, reputation 0-100)
 *   - Kompletność danych (6 pól na bohatera)
 * 
 * Funkcja zwraca kod błędu (FILE_OK = sukces, inne = błąd).
 * Jeśli sukces, *out_list wskazuje na nową listę bohaterów.
 */
FileErrorCode load_list_from_file(const char* file_path, HeroList** out_list);

/**
 * Sprawdza czy plik istnieje na dysku.
 *
 * const char* file_path - Ścieżka do pliku.
 * 
 * Funkcja zwraca FILE_OK jeśli plik istnieje, FILE_NOT_FOUND jeśli nie.
 */
FileErrorCode file_exists(const char* file_path);

#endif // FILE_HANDLER_H