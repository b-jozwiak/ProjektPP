#include <stdio.h>
#include "text_input_handler.h"
#include <stdlib.h>
#include <string.h>


void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int read_integer(const char* prompt) {
    int value;
    while (1) {
        if (prompt != NULL) {
            printf("%s", prompt);
        }
        if (scanf("%d", &value) != 1) {
            printf("Nieprawidlowe dane. Sprobuj ponownie.\n");
            clear_input();
        } else {
            return value;
        }
    }
}

int read_integer_range(const char* prompt, int min, int max) {
    int value;
    while (1) {
        if (prompt != NULL) {
            printf("%s", prompt);
        }
        if (scanf("%d", &value) != 1) {
            printf("Nieprawidlowe dane. Sprobuj ponownie.\n");
            clear_input();
        } else if (value < min || value > max) {
            printf("Wartosc musi byc w zakresie od %d do %d. Sprobuj ponownie.\n", min, max);
        } else {
            return value;
        }
    }
}

int read_string(const char* prompt, char* buffer, size_t max_length) {
    clear_input();
    if (prompt != NULL) {
        printf("%s", prompt);
    }
    if (fgets(buffer, max_length, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            clear_input();
        }
        return 1;
    }
    return 0;
}