# Rejestr Bohaterów Gildii Poszukiwaczy Przygód

**Przedmiot:** Podstawy Programowania (PS4)  
**Temat:** 2. Rejestr Bohaterów Gildii Poszukiwaczy Przygód  
**Autor:** Bartosz Jóźwiak, 119694 - Informatyka, 1 semestr

---

## Opis projektu

Program umożliwia zarządzanie rejestrem bohaterów dla Gildii Poszukiwaczy Przygód, w tym:

- Rejestrację nowych bohaterów z walidacją unikalności imienia
- Edycję danych bohaterów (z ochroną pola imienia)
- Wyszukiwanie i filtrowanie bohaterów (9 kryteriów)
- Sortowanie bohaterów (6 sposobów)
- Usuwanie bohaterów (z ochroną dla tych "na misji")
- Trwały zapis i odczyt z pliku tekstowego
- Intuicyjne menu tekstowe

---

## Kompilacja i uruchomienie

### Kompilacja

**Przy użyciu Make:**
```bash
make
```

**Ręczna kompilacja:**
```bash
gcc -Wall -Wextra -std=c99 -o out/rejestr \
    src/*.c src/hero/*.c src/io/*.c src/ui/*.c src/util/*.c
```

### Uruchomienie

Program pisany i uruchamiany za pomocą WSL (Ubuntu).<br>
Natywne działanie na systemie Windows nie jest gwarantowane.

Program wymaga podania ścieżki do pliku danych:

```bash
./out/rejestr bohaterowie.txt
```

Jeśli podana zostanie tylko jedna ścieżka, będzie ona używana zarówno do wczytania jak i zapisu.

**Opcjonalnie - różne ścieżki wczytania i zapisu:**
```bash
./out/rejest wczytaj.txt zapisz.txt
```

### Czyszczenie kompilacji
```bash
make clean
```

---

## Dane bohatera

Każdy bohater zawiera:

| Pole | Typ | Opis | Edytowalne |
|------|-----|------|-----------|
| **Imię** | Tekst (50 zn.) | Unikalne, identyfikator bohatera | Nie |
| **Rasa** | Enum | Człowiek, Elf, Krasnolud, Ork, Tiefling | Tak |
| **Klasa** | Enum | Wojownik, Mag, Kapłan, Łotrzyk, Łowca, Druid | Tak |
| **Poziom doświadczenia** | Int (1-100) | Ogólny poziom rozwoju | Tak |
| **Reputacja** | Int (0-100) | Opinia o bohaterze w gildii | Tak |
| **Status** | Enum | Aktywny, Na misji, Ranny, Zaginiony, Zawieszony | Tak |

---

## Menu główne

```
====== Rejestr Gildii Poszukiwaczy Przygod ======
1. Zarejestruj nowego bohatera
2. Zarządzaj bohaterami
3. Wczytaj bohaterów z pliku
4. Zapisz bohaterów do pliku
0. Zamknij program
```

### 1. Rejestracja nowego bohatera
- Pytanie o unikalne imię (walidacja duplikatów)
- Wybór rasy spośród 5 opcji
- Wybór klasy spośród 6 opcji
- Podanie poziomu doświadczenia (1-100)
- Podanie reputacji (0-100)
- Domyślny status: ACTIVE

### 2. Zarządzanie bohaterami
Otwiera submenu z opcjami:
- Wyświetl listę
- Wyczyść filtry
- Wyszukaj bohaterów
- Sortuj bohaterów
- Edytuj bohaterów
- Usuń bohaterów
- Zapisz wybór do pliku

### 3. Wczytaj bohaterów z pliku
- Wczytuje listę z podanej ścieżki
- Waliduje format i dane
- Zamienia aktualną listę

### 4. Zapisz bohaterów do pliku
- Zapisuje aktualną listę
- Bezpieczne zamknięcie pliku

---

## Filtrowanie (9 kryteriów)

| Opcja | Kryterium | Typ |
|-------|-----------|-----|
| 1 | Pełne imię | Tekst (dokładne dopasowanie) |
| 2 | Prefiks imienia | Tekst (prefiksowe dopasowanie) |
| 3 | Poziom >= | Liczba |
| 4 | Poziom <= | Liczba |
| 5 | Reputacja >= | Liczba |
| 6 | Reputacja <= | Liczba |
| 7 | Rasa | Enum |
| 8 | Klasa | Enum |
| 9 | Status | Enum |

---

## Sortowanie (6 sposobów)

| Opcja | Kryterium |
|-------|-----------|
| 1 | Po imieniu (A-Z lub Z-A) |
| 2 | Po poziomie doświadczenia |
| 3 | Po reputacji |
| 4 | Po rasie |
| 5 | Po klasie |
| 6 | Po statusie |

Każde sortowanie pozwala wybrać kierunek (rosnąco/malejąco).

---

## Edycja bohaterów
Edycja bohaterów dzieje się na podzbiorach głównej listy. <br>
Oznacza to, że można edytować wybraną listę (jednego bądź więcej) bohaterów jednocześnie. 

Można edytować:
- Poziom doświadczenia
- Reputacja
- Status
- Klasa
- Rasa

**Chronione:**
- Imię (nie można zmienić po rejestracji)

---

## Usuwanie bohaterów

- Można usunąć jednego *bądź wielu* bohaterów za pomocą filtrów podczas zarządzania rejestrem
- **OCHRONA:** Nie można usunąć bohatera ze statusem "Na misji"
- Wymaga potwierdzenia przed usunięciem

---

## Format pliku

Plik tekstowy z bohaterami w formacie:

```
HERO_LIST 3
Aragorn;0;0;50;85;0
Gandalf;1;1;99;100;0
Legolas;1;4;45;90;0
```

### Struktura:
- Wiersz 1: `HERO_LIST N` (N = liczba bohaterów)
- Wiersze 2+: `name;race;class;level;reputation;status`

### Kodowanie enumeracji:

**Rasa:**
- 0 = Człowiek
- 1 = Elf
- 2 = Krasnolud
- 3 = Ork
- 4 = Tiefling

**Klasa:**
- 0 = Wojownik
- 1 = Mag
- 2 = Kapłan
- 3 = Łotrzyk
- 4 = Łowca
- 5 = Druid

**Status:**
- 0 = Aktywny
- 1 = Na misji
- 2 = Ranny
- 3 = Zaginiony
- 4 = Zawieszony

---

## Implementacja

### Dynamiczna lista bohaterów
- Początkowa pojemność: 10 bohaterów
- Automatyczne rozszerzenie (2x) gdy pełna
- Dynamiczna alokacja pamięci (`malloc`/`realloc`)

### System filtrowania i sortowania
- Filtry/sortowanie tworzą "podzbiory" (is_root=false)
- Bohaterowie nie są kopiowani, tylko wskaźniki
- Główna lista zawsze ma rzeczywistych bohaterów

### Bezpieczne zarządzanie pamięcią
- `is_root=true` - uwalniam bohaterów oraz strukturę listy
- `is_root=false` - tylko strukturę listy
- Brak wycieków w ścieżkach błędów

---

## Dokumentacja kodu

Wszystkie publiczne funkcje są udokumentowane w plikach nagłówkowych (.h) w formacie:

```c
/**
 * Krótki opis funkcji.
 *
 * parametr1 - Opis parametru 1.
 * parametr2 - Opis parametru 2.
 * 
 * Funkcja zwraca: Typ i opis zwracanej wartości.
 */
```



