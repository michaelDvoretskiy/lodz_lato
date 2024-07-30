#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* create_arr(int size) {
    int* num;
    num = malloc(sizeof(int) * size);
    if (num == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        *(num + i) = rand() % 1001;
    }

    return num;
}

void show_numbers(int* numbers, int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", *(numbers + i));
    }
    printf("\n");
}


int main() {
    srand(time(NULL));
    int* nums = create_arr(10);
    if (nums == NULL) {
        return 1;
    }
    show_numbers(nums, 10);
    free(nums);
    return 0;
}
