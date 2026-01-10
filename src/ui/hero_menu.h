#ifndef HERO_MENU_H
#define HERO_MENU_H

#include "../hero/hero_list.h"

/**
 * Funkcja wyświetlająca menu zarządzania bohaterami.
 *
 * HeroList* hero_list - Wskaźnik do głównej listy bohaterów.
 * const char* output_file - Domyślna ścieżka do pliku zapisu bohaterów.
 * 
 * Menu umożliwia:
 *   - Wyświetlanie listy bohaterów
 *   - Czyszczenie filtrów
 *   - Wyszukiwanie i filtrowanie (9 kryteriów)
 *   - Sortowanie (6 sposobów)
 *   - Edycję danych bohaterów
 *   - Usuwanie bohaterów
 *   - Zapis wybranej listy do pliku
 * 
 * Funkcja nic nie zwraca. Wraca do menu głównego po wyborze opcji 0.
 */
void hero_menu(HeroList* hero_list, const char* output_file);

#endif // HERO_MENU_H