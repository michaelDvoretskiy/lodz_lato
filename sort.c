#include <stdio.h>
#include "sort.h"

int compare_int(const void* x, const void* y) {
    return *((int*) x) - *((int*) y);
}

int compare_float(const void* x, const void* y) {
    float res = *((float*) x) - *((float*) y);
    if (res > 0) {
        return 1;
    }
    if (res < 0) {
        return -1;
    }
    return 0;
}

int compare_point(const void* p1, const void* p2) {
    struct point_t* point1 = (struct point_t*) p1;
    struct point_t* point2 = (struct point_t*) p2;
    int res = point1->x - point2->x;
    if (res > 0) {
        return 1;
    }
    if (res < 0) {
        return -1;
    }
    return point1->y - point2->y;
}

void sort_array(void* array, size_t elements_in_array, size_t elem_size, int (*comparator)(const void*, const void*)) {
    char* array_of_bytes = (char*) array;

    for (size_t i = 0; i < elements_in_array; i++) {
        char* i_element_start = array_of_bytes + i * elem_size;
        for (size_t j = i + 1; j < elements_in_array; j++) {
            char* j_element_start = array_of_bytes + j * elem_size;
            if (comparator((const void *)(i_element_start), (const void *) (j_element_start)) > 0) {
                for (size_t k = 0; k < elem_size; k++) {
                    char temp = *(i_element_start + k);
                    *(i_element_start + k) = *(j_element_start + k);
                    *(j_element_start + k) = temp;
                }
            }
        }
    }
}