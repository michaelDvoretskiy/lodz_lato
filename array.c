#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void create_arr(int*** arr, int rows, int cols, int* err_code) {
    *err_code = 0;
    *arr = malloc(sizeof(int*) * rows);
    if (*arr == NULL) {
        *err_code = 1;
        return;
    }
    for (int i = 0; i < rows; i++) {
        *(*arr + i) = malloc(sizeof(int) * cols);
        if (*(*arr + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(*arr + j));
            }
            free(*arr);
            *err_code = 1;
            return;
        }
    }
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

void destroy_arr(int*** arr, int rows, int* err_code) {
    *err_code = 0;
    if (arr == NULL || *arr == NULL) {
        *err_code = 1;
        return;
    }
    for (int i = 0; i < rows; i++) {
        free(*(*arr + i));
    }
    free(*arr);
}