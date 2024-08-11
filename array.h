#ifndef CODE_ARRAY_H
#define CODE_ARRAY_H

struct matrix_t {
    int** arr;
    int rows;
    int cols;
};

struct matrix_t* create_matrix(int rows, int cols);

void show_matrix(struct matrix_t* m);

void destroy_matrix(struct matrix_t*);

int matrix_save_binary(const struct matrix_t *m, const char *filename);

int matrix_save_text(const struct matrix_t *m, const char *filename);

struct matrix_t* matrix_load_binary(const char *filename, int *err_code);

struct matrix_t* matrix_load_text(const char *filename, int *err_code);

#endif //CODE_ARRAY_H
