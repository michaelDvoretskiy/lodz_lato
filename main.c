#include <stdio.h>
#include <stdlib.h>

int main() {
    int arr_size = 5;

    int* num = malloc(sizeof(int) * arr_size);
    if (num == NULL) {
        return 1;
    }

    for (int i = 0; i < arr_size; i++) {
        *(num + i) = (i + 1) * 10;
    }

    for (int i = 0; i < arr_size; i++) {
        printf("%d ", *(num + i));
    }
    printf("\n");

    free(num);
    return 0;
}
