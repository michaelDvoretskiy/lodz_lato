#include <stdio.h>
#include <stdlib.h>

void create_nums(int** nums_p, int arr_size) {
    if (nums_p == NULL) {
        return;
    }
    *nums_p = malloc(sizeof(int) * arr_size);
    if (*nums_p == NULL) {
        return;
    }
    for (int i = 0; i < arr_size; i++) {
        *(*nums_p + i) = rand() % 1001;
    }
}

void show_nums(int* numbers, int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", *(numbers + i));
    }
    printf("\n");
}

void destroy_nums(int** nums_p, int arr_size) {
    if (nums_p == NULL) {
        return;
    }
    if (*nums_p != NULL) {
        free(*nums_p);
    }
    free(nums_p);
}

int main() {
    int** numbers_pointer = malloc(sizeof(int*));
    create_nums(numbers_pointer, 10);
    show_nums(*numbers_pointer, 10);
    destroy_nums(numbers_pointer, 10);
    return 0;
}
