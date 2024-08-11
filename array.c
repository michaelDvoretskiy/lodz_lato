#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int** create_arr(int rows, int cols) {
    int** arr = malloc(sizeof(int*) * rows);
    if (arr == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        *(arr + i) = malloc(sizeof(int) * cols);
        if (*(arr + i) == NULL) {
            destroy_arr(arr, rows);
            return NULL;
        }
    }

    return arr;
}

void show_arr(int** arr, int rows, int cols) {
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        if (*(arr + i) == NULL) {
            return;
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("==========\n");
}

void destroy_arr(int** arr, int rows) {
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        if (*(arr + i) != NULL) {
            free(*(arr + i));
        }
    }
    free(arr);
}