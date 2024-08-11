#include <stdio.h>
#include "array.h"

int main() {
    char* binary_filename = "binary_input";
    char* text_filename = "text_input.txt";

    int err;

    struct matrix_t* m = matrix_load_binary(binary_filename, &err);
    if (m == NULL || err != 0) {
        return 1;
    }

    show_matrix(m);
    *(*(m->arr+2)+2) = 1000;
    show_matrix(m);
    matrix_save_binary(m, binary_filename);

    destroy_matrix(m);

    m = matrix_load_text(text_filename, &err);
    if (m == NULL || err != 0) {
        return 1;
    }

    show_matrix(m);
    *(*(m->arr+2)+2) = 1000;
    show_matrix(m);
    matrix_save_text(m, text_filename);

    destroy_matrix(m);

    return 0;
}
