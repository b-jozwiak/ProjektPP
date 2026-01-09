#ifndef TEXT_INPUT_HANDLER_H
#define TEXT_INPUT_HANDLER_H
void clear_input();

/** 
 *  Funckja wczytuje liczbe calkowita z wejscia standardowego do skutku. 
 *
 *  const char* prompt - Komunikat do wyswietlenia przed wczytaniem.
 *  Funckja zwraca wczytana liczba calkowita.
 */
int read_integer(const char* prompt);

/** 
 *  Funckja wczytuje liczbe calkowita z wejscia standardowego do skutku. 
 *
 *  const char* prompt - Komunikat do wyswietlenia przed wczytaniem.
 *  int min - Minimalna dopuszczalna wartosc.
 *  int max - Maksymalna dopuszczalna wartosc.
 *
 *  Funckaj zwraca wczytana liczba calkowita.
 */
int read_integer_range(const char* prompt, int min, int max);

/** 
 *  Funckja wczytuje lancuch znakow z wejscia standardowego.
 *
 *  const char* prompt - Komunikat do wyswietlenia przed wczytaniem.
 *  char* buffer - Bufor do przechowania wczytanego lancucha znakow.
 *  size_t max_length - Maksymalna dlugosc lancucha znakow do wczytania (wraz z znakiem konca lancucha).
 *  Funkcja zwraca 1 w przypadku powodzenia, 0 w przypadku bledu.
 */
int read_string(const char* prompt, char* buffer, size_t max_length);

#endif // TEXT_INPUT_HANDLER_H