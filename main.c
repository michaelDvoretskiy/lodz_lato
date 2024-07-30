#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 5

void set_values(int* numbers) {
    if (numbers == NULL) {
        return;
    }
    for (int i = 0; i < ARR_SIZE; i++) {
        *(numbers + i) = rand() % 1001;
    }
}

void show_numbers(int* numbers) {
    for (int i = 0; i < ARR_SIZE; i++) {
        printf("%d ", *(numbers + i));
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int* num_arr = malloc(sizeof(int) * ARR_SIZE);
    if (num_arr == NULL) {
        return 1;
    }
    set_values(num_arr);
    show_numbers(num_arr);
    free(num_arr);

    printf("================\n");

    int numbers2[ARR_SIZE];
    set_values(numbers2);
    show_numbers(numbers2);

    return 0;
}
