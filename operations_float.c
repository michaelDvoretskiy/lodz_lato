#include <stdio.h>
#include <stdlib.h>
#include "operations_float.h"

void* add_float(const void* x, const void* y) {
    if (x == NULL || y == NULL) {
        return NULL;
    }

    float* result = malloc(sizeof(int));
    if (!result) {
        return NULL;
    }

    *result = *((float*)x) + *((float*)y);

    return result;
}

void* sub_float(const void* x, const void* y) {
    if (x == NULL || y == NULL) {
        return NULL;
    }

    float* result = malloc(sizeof(int));
    if (!result) {
        return NULL;
    }

    *result = *((float*)x) - *((float*)y);

    return result;
}

int read_input_float(void** x, void** y) {
    *x = malloc(sizeof(float*));
    *y = malloc(sizeof(float*));

    float a, b;
    printf("Enter two numbers:");
    if (scanf("%f %f", &a, &b) != 2) {
        return 1;
    }
    *((float*) *x) = a;
    *((float*) *y) = b;

    return 0;
}

void show_result_float(void* res) {
    if (res == NULL) {
        return;
    }
    printf("%f\n", *((float*)res));
}