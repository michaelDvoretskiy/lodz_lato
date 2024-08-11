#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

int main() {
    short* arr1 = create_arr(3);
    if (arr1 == NULL) {
        return 1;
    }

    short* arr2 = create_arr(3);
    if (arr2 == NULL) {
        free(arr1);
        return 1;
    }

    for (short i = 0; i < 3; i++) {
        *(arr1 + i) = i;
        *(arr2 + i) = 10*i;
    }
    show_arr(arr1, 3);
    show_arr(arr2, 3);

    short* arr3 = concat_arr(arr1, 3, arr2, 3);
    if (arr3 == NULL) {
        free(arr1);
        free(arr2);
        return 1;
    }
    show_arr(arr3, 6);

    short* arr4 = create_arr(9);
    if (arr4 == NULL) {
        free(arr1);
        free(arr2);
        free(arr3);
        return 1;
    }
    int err;
    concat_arr2(arr3, 6, arr1, 3, &arr4, &err);
    if (err != 0) {
        free(arr1);
        free(arr2);
        free(arr3);
        free(arr4);
        return 1;
    }
    show_arr(arr4, 9);

    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);

    return 0;
}
