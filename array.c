#include <stdio.h>
#include <stdlib.h>
#include "array.h"

struct matrix_t* create_matrix(int rows, int cols) {
    struct matrix_t* m = malloc(sizeof(struct matrix_t));
    if (m == NULL) {
        return NULL;
    }

    m->rows = rows;
    m->cols = cols;

    m->arr = malloc(sizeof(int*) * rows);
    if (m->arr == NULL) {
        free(m->arr);
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        *(m->arr + i) = malloc(sizeof(int) * cols);
        if (*(m->arr + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(m->arr + j));
            }
            free(m->arr);
            free(m);
            return NULL;
        }
    }

    return m;
}

void show_matrix(struct matrix_t* m) {
    if (m == NULL || m->arr == NULL) {
        return;
    }
    for (int i = 0; i < m->rows; i++) {
        if (*(m->arr + i) == NULL) {
            return;
        }
    }
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%d ", *(*(m->arr + i) + j));
        }
        printf("\n");
    }
    printf("==========\n");
}

void destroy_matrix(struct matrix_t* m) {
    if (m == NULL || m->arr == NULL) {
        return;
    }
    for (int i = 0; i < m->rows; i++) {
        free(*(m->arr + i));
    }
    free(m->arr);
    free(m);
}