#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int my_sum(int* res, ...) {
    if (res == NULL){
        return 1;
    }

    va_list args;
    va_start(args, res);

    *res = 0;
    int* next_arg = va_arg(args, int*);
    while (next_arg != NULL) {
        *res += *next_arg;
        next_arg = va_arg(args, int*);
    }

    va_end(args);

    return 0;
}

int main() {
    int arr_size;
    printf("Enter number of elements:");
    if (scanf("%d", &arr_size) != 1) {
        printf("Incorrect input\n");
        return 1;
    }

    if (arr_size < 1 || arr_size > 3) {
        printf("Incorrect input data\n");
        return 2;
    }

    int* arr_int = (int*) malloc(arr_size * sizeof(int));
    if (!arr_int) {
        printf("Memory allocation error\n");
        return 1;
    }

    printf("Enter numbers:");
    for (int i = 0; i < arr_size; i++) {
        if (scanf("%d", (arr_int + i)) != 1) {
            printf("Incorrect input\n");
            free(arr_int);
            return 1;
        }
    }

    int sum_value, res;

    res = my_sum(
            &sum_value,
            arr_int,
            arr_size > 1 ? (arr_int + 1) : NULL,
            arr_size > 2 ? (arr_int + 2) : NULL,
            arr_size > 3 ? (arr_int + 3) : NULL,
            NULL
    );
    if (res == 0) {
        printf("sum: %d\n", sum_value);
    } else {
        return 1;
    }

    return 0;
}