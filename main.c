#include <stdio.h>
#include <stdlib.h>

void show_arr(int* arr, int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%hd ", *(arr + i));
    }
    printf("\n");
    printf("==============\n");
}

void reverse(int* arr, int size) {
    int* first = arr;
    int* last = arr + size - 1;

    while (first < last) {
        int tmp = *first;
        *first = *last;
        *last = tmp;

        first++;
        last--;
    }
}

int main() {
    int* arr = malloc(sizeof(int) * 10);
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < 10; i++) {
        *(arr + i) = i;
    }
    show_arr(arr, 10);

    reverse(arr, 10);
    show_arr(arr, 10);

    return 0;
}
