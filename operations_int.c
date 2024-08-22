#include <stdio.h>
#include <stdlib.h>
#include "operations_int.h"

void* add_int(const void* x, const void* y) {
    if (x == NULL || y == NULL) {
        return NULL;
    }

    int* result = malloc(sizeof(int));
    if (!result) {
        return NULL;
    }

    *result = *((int*)x) + *((int*)y);

    return result;
}

void* sub_int(const void* x, const void* y) {
    if (x == NULL || y == NULL) {
        return NULL;
    }

    int* result = malloc(sizeof(int));
    if (!result) {
        return NULL;
    }

    *result = *((int*)x) - *((int*)y);

    return result;
}

int read_input_int(void** x, void** y) {
    *x = malloc(sizeof(int*));
    *y = malloc(sizeof(int*));

    int a, b;
    printf("Enter two numbers:");
    if (scanf("%d %d", &a, &b) != 2) {
        return 1;
    }
    *((int*) *x) = a;
    *((int*) *y) = b;

    return 0;
}

void show_result_int(void* res) {
    if (res == NULL) {
        return;
    }
    printf("%d\n", *((int*)res));
}