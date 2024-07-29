#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void set_values(int* numbers, int arr_size) {
    if (numbers == NULL) {
        return;
    }
    for (int i = 0; i < arr_size; i++) {
        *(numbers + i) = rand() % 1001;
    }
}

void show_numbers(int* numbers, int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        printf("%d ", *(numbers + i));
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int num_arr_size = 5;
    int* num_arr = malloc(sizeof(int) * num_arr_size);
    if (num_arr == NULL) {
        return 1;
    }
    set_values(num_arr, num_arr_size);
    show_numbers(num_arr, num_arr_size);
    free(num_arr);

    printf("================\n");

    int numbers2[num_arr_size];
    set_values(numbers2, num_arr_size);
    show_numbers(numbers2, num_arr_size);

    return 0;
}
