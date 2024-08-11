#include <stdio.h>
#include "array.h"

int main() {
    int** multiple = create_arr(10, 10);
    if (multiple == NULL) {
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            *(*(multiple + i) + j) = (i + 1) * (j + 1);
        }
    }

    show_arr(multiple, 10, 10);

    return 0;
}
