#ifndef CODE_ARRAY_H
#define CODE_ARRAY_H

void create_arr(int*** arr, int rows, int cols, int* err_code);

void show_arr(int** arr, int rows, int cols);

void destroy_arr(int*** arr, int rows, int* err_code);

#endif //CODE_ARRAY_H
