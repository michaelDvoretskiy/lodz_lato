#include <stdio.h>
#include <stdlib.h>
#include "operations_point.h"

void* add_point(const void* p1, const void* p2) {
    if (p1 == NULL || p2 == NULL) {
        return NULL;
    }

    struct point_t* result = malloc(sizeof(struct point_t));
    if (!result) {
        return NULL;
    }

    result->x = ((struct point_t*)p1)->x + ((struct point_t*)p2)->x;
    result->y = ((struct point_t*)p1)->y + ((struct point_t*)p2)->y;

    return result;
}

void* sub_point(const void* p1, const void* p2) {
    if (p1 == NULL || p2 == NULL) {
        return NULL;
    }

    struct point_t* result = malloc(sizeof(struct point_t));
    if (!result) {
        return NULL;
    }

    result->x = ((struct point_t*)p1)->x - ((struct point_t*)p2)->x;
    result->y = ((struct point_t*)p1)->y - ((struct point_t*)p2)->y;

    return result;
}

int read_input_point(void** p1, void**p2) {
    *p1 = malloc(sizeof(struct point_t));
    *p2 = malloc(sizeof(struct point_t));

    int x1, y1, x2, y2;
    printf("Enter coordinates (x1 y1 x2 y2):");
    if (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != 4) {
        return 1;
    }
    ((struct point_t*)(*p1))->x = x1;
    ((struct point_t*)(*p1))->y = y1;
    ((struct point_t*)(*p2))->x = x2;
    ((struct point_t*)(*p2))->y = y2;

    return 0;
}

void show_result_point(void* res) {
    if (res == NULL) {
        return;
    }
    printf("%d %d\n", ((struct point_t*)res)->x, ((struct point_t*)res)->y);
}