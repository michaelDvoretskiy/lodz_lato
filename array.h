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

#endif //CODE_ARRAY_H
