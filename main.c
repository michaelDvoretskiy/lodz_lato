#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int main() {
    int int_array[] = {1, 5, -6, 10, 20};
    float float_array[] = {10.2f, 5.34f, -6.8f, 1.01f, 0.20f};
    struct point_t* point_array = malloc(sizeof(struct point_t) * 5);
    point_array->x = 10; point_array->y = 20;
    (point_array+1)->x = 5; (point_array+1)->y = 18;
    (point_array+2)->x = 5; (point_array+2)->y = 13;
    (point_array+3)->x = 12; (point_array+3)->y = -4;
    (point_array+4)->x = -5; (point_array+4)->y = 18;

    sort_array(int_array, 5, sizeof(int), compare_int);
    sort_array(float_array, 5, sizeof(float), compare_float);
    sort_array(point_array, 5, sizeof(struct point_t), compare_point);

    for (int i = 0; i < 5; i++) {
        printf("%d ", *(int_array + i));
    }
    printf("\n");

    for (int i = 0; i < 5; i++) {
        printf("%f ", *(float_array + i));
    }
    printf("\n");

    for (int i = 0; i < 5; i++) {
        printf("(%d %d) ", (point_array + i)->x, (point_array + i)->y);
    }
    printf("\n");

    return 0;
}
