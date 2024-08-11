#include <stdio.h>
#include "array.h"

int main() {
    int** multiple;
    int err;
    create_arr(&multiple, 10, 10, &err);
    if (err != 0) {
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            *(*(multiple + i) + j) = (i + 1) * (j + 1);
        }
    }

    show_arr(multiple, 10, 10);

    destroy_arr(&multiple, 10, &err);
    if (err != 0) {
        return 1;
    }

    return 0;
}
