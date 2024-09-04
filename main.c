#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    int size = 3;
    int* int_values = malloc(sizeof(int) * size);
    read_int(int_values, size);
    display_int(int_values, size);
    free(int_values);

    float* float_value = malloc(sizeof(float) * size);
    read_float(float_value, size);
    display_float(float_value, size);
    free(float_value);

    return 0;
}
