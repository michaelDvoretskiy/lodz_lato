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

int matrix_save_binary(const struct matrix_t *m, const char *filename) {
    if (!m || m->cols <= 0 || m->rows <= 0 || !m->arr || !filename) {
        return 1;
    }

    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 2;
    }

    fwrite(&(m->cols), sizeof(int), 1, file);
    fwrite(&(m->rows), sizeof(int), 1, file);

    for (int i = 0; i < m->rows; i++) {
        fwrite(*(m->arr + i), sizeof(int), m->cols, file);
    }

    fclose(file);
    return 0;
}

int matrix_save_text(const struct matrix_t *m, const char *filename) {
    if (!m || m->cols <= 0 || m->rows <= 0 || !m->arr || !filename) {
        return 1;
    }

    FILE *file = fopen(filename, "w");
    if (!file) {
        return 2;
    }

    fprintf(file, "%d %d\n", m->cols, m->rows);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            fprintf(file, "%d ", *(*(m->arr + i) + j));
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

struct matrix_t* matrix_load_binary(const char *filename, int *err_code) {

    if (!filename) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return NULL;
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        if (err_code != NULL) {
            *err_code = 2;
        }
        return NULL;
    }

    int cols, rows;
    if (fread(&cols, sizeof(int), 1, file) != 1 || fread(&rows, sizeof(int), 1, file) != 1) {
        fclose(file);
        if (err_code != NULL) {
            *err_code = 3;
        }
        return NULL;
    }

    if (cols <= 0 || rows <= 0) {
        fclose(file);
        if (err_code != NULL) {
            *err_code = 3;
        }
        return NULL;
    }

    struct matrix_t *m = create_matrix(rows, cols);
    if (!m) {
        fclose(file);
        if (err_code != NULL) {
            *err_code = 4;
        }
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        if (fread(*(m->arr+i), sizeof(int), cols, file) != (long unsigned int)cols) {
            fclose(file);
            destroy_matrix(m);
            if (err_code != NULL) {
                *err_code = 3;
            }
            return NULL;
        }
    }

    fclose(file);
    if (err_code != NULL) {
        *err_code = 0;
    }
    return m;
}

struct matrix_t* matrix_load_text(const char *filename, int *err_code) {
    if (!filename) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        if (err_code != NULL) {
            *err_code = 2;
        }
        return NULL;
    }

    int cols, rows;
    if (fscanf(file, "%d %d", &cols, &rows) != 2) {
        fclose(file);
        if (err_code != NULL) {
            *err_code = 3;
        }
        return NULL;
    }

    if (cols <= 0 || rows <= 0) {
        fclose(file);
        if (err_code != NULL) {
            *err_code = 3;
        }
        return NULL;
    }
    struct matrix_t *m = create_matrix(rows, cols);
    if (!m) {
        fclose(file);
        if (err_code != NULL) {
            *err_code = 4;
        }
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(file, "%d", (*(m->arr + i) + j)) != 1) {
                fclose(file);
                destroy_matrix(m);
                if (err_code != NULL) {
                    *err_code = 3;
                }
                return NULL;
            }
        }
    }

    fclose(file);
    if (err_code != NULL) {
        *err_code = 0;
    }
    return m;
}