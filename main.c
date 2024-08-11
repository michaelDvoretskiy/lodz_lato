#include <stdio.h>
#include "array.h"

int main() {
    struct matrix_t* m = create_matrix(10, 10);
    if (m == NULL) {
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            *(*(m->arr + i) + j) = (i + 1) * (j + 1);
        }
    }

    show_matrix(m);

    destroy_matrix(m);

    return 0;
}
