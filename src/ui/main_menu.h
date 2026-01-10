#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../hero/hero_list.h"

/**
 * Funkcja wyświetlająca główne menu aplikacji.
 *
 * HeroList** hero_list - Wskaźnik do wskaźnika listy bohaterów 
 *                         (może być zmieniana przy wczytywaniu z pliku).
 * const char* input_file - Domyślna ścieżka do pliku wczytania bohaterów.
 * const char* output_file - Domyślna ścieżka do pliku zapisu bohaterów.
 * 
 * Menu umożliwia:
 *   1. Rejestrację nowego bohatera
 *   2. Dostęp do menu zarządzania bohaterami
 *   3. Wczytanie bohaterów z pliku
 *   4. Zapis bohaterów do pliku
 *   0. Wyjście z programu
 * 
 * Funkcja nic nie zwraca. Pętla się, aż użytkownik wybierze opcję 0.
 */
void main_menu(HeroList** hero_list, const char* input_file, const char* output_file);

#endif // MAIN_MENU_H