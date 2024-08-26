#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "my_strings.h"

int read_number_of_texts(int* number_of_texts) {
    printf("Enter the number of texts to enter (from 2 to 4):");
    if (scanf("%d", number_of_texts) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (*number_of_texts < 2 || *number_of_texts > 4) {
        printf("Incorrect input data");
        return 2;
    }
    return 0;
}

int create_texts(char*** texts, int number_of_texts) {
    *texts = (char**) malloc(number_of_texts * sizeof(char*));
    if (*texts == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    for (int i = 0; i < number_of_texts; i++) {
        *(*texts + i) = NULL;
    }

    for (int i = 0; i < number_of_texts; i++) {
        *(*texts + i) = (char*) malloc(ONE_TEXT_SIZE * sizeof(char));
        if (*(*texts + i) == NULL) {
            destroy_texts(*texts, number_of_texts);
            printf("Failed to allocate memory");
            return 8;
        }
    }

    return 0;
}

void clear (void) {
    while ( getchar() != '\n' );
}

int read_texts(char** texts, int number_of_texts) {
    printf("Enter text:\n");
    clear();

    for (int i = 0; i < number_of_texts; i++) {
        int characters_number = 0;
        char c = getchar();
        while (c != '\n') {
            if (characters_number < ONE_TEXT_SIZE) {
                *(*(texts + i) + characters_number) = c;
                characters_number++;
            }
            c = getchar();
        }
        *(*(texts + i) + characters_number) = '\0';
    }

    return 0;
}

void display_texts(char** texts, int number_of_texts) {
    if (texts == NULL) {
        return;
    }
    for (int i = 0; i < number_of_texts; i++) {
        printf("%s\n", *(texts + i));
    }
    printf("======================\n");
}

void destroy_texts(char** texts, int number_of_texts) {
    if (texts == NULL) {
        return;
    }
    for (int i = 0; i < number_of_texts; i++) {
        if (*(texts + i) != NULL) {
            free(*(texts + i));
        }
    }
    free(texts);
}

int concat_texts(char** text_result, int number_of_texts, ...) {
    if (text_result == NULL || number_of_texts <= 0) {
        return 1;
    }

    *text_result = (char*) malloc((ONE_TEXT_SIZE + 1) * 4 * sizeof(char));
    if (*text_result == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    va_list args;
    va_start(args, number_of_texts);

    char* one_text = va_arg(args, char*);
    strcpy(*text_result, one_text);

    for (int i = 1; i < number_of_texts; i++) {
        one_text = va_arg(args, char*);
        if (one_text == NULL) {
            va_end(args);
            free(*text_result);
            return 1;
        }

        if (i > 0) {
            strcat(*text_result, " ");
        }
        strcat(*text_result, one_text);
    }

    va_end(args);

    return 0;
}