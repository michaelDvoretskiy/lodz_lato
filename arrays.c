#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

short* create_arr(int size) {
    if (size <= 0) {
        return NULL;
    }

    short* arr = malloc(sizeof(short) * size);
    if (arr == NULL) {
        return NULL;
    }

    return arr;
}

void show_arr(short* arr, int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%hd ", *(arr + i));
    }
    printf("\n");
    printf("==============\n");
}

short* concat_arr(short* arr1, int size1, short* arr2, int size2) {
    if (arr1 == NULL || arr2 == NULL) {
        return NULL;
    }
    if (size1 <= 0 || size2 <= 0) {
        return NULL;
    }

    short* new_arr = malloc(sizeof(short ) * (size1 + size2));
    if (new_arr == NULL) {
        return NULL;
    }
    for (int i = 0; i < size1; i++) {
        *(new_arr + i) = *(arr1 + i);
    }
    for (int i = 0; i < size2; i++) {
        *(new_arr + size1 + i) = *(arr2 + i);
    }

    return new_arr;
}

void concat_arr2(short* arr1, int size1, short* arr2, int size2, short** new_arr, int* err_code) {
    *err_code = 0;
    if (arr1 == NULL || arr2 == NULL) {
        *err_code = 1;
        return;
    }
    if (size1 <= 0 || size2 <= 0) {
        *err_code = 2;
        return;
    }

    if (new_arr == NULL || *new_arr == NULL) {
        *err_code = 3;
        return;
    }

    for (int i = 0; i < size1; i++) {
        *(*new_arr + i) = *(arr1 + i);
    }
    for (int i = 0; i < size2; i++) {
        *(*new_arr + size1 + i) = *(arr2 + i);
    }
}