#include <stdio.h>
#include <stdlib.h>

struct point_t {
    int x;
    int y;
};

void* add_int(const void* x, const void* y) {
    int* result = malloc(sizeof(int));
    if (!result) {
        return NULL;
    }

    *result = *((int*)x) + *((int*)y);

    return result;
}

void* add_float(const void* x, const void* y) {
    float* result = malloc(sizeof(float));
    if (!result) {
        return NULL;
    }

    *result = *((float*)x) + *((float*)y);

    return result;
}

const void* add_point(const void* p1, const void* p2) {
    struct point_t* new_point = malloc(sizeof(struct point_t));
    new_point->x = ((struct point_t*)p1)->x + ((struct point_t*)p2)->x;
    new_point->y = ((struct point_t*)p1)->y + ((struct point_t*)p2)->y;

    return new_point;
}

int main() {
    void* (*add)(const void*, const void*);

    int x_int = 10, y_int = 20;
    add = add_int;
    int* res_int = add((const void*)(&x_int), (const void*)(&y_int));
    printf("%d\n", *res_int);
    free(res_int);

    float x_float = 10.5f, y_float = 2.05f;
    add = add_float;
    float* res_float = add((const void*)(&x_float), (const void*)(&y_float));
    printf("%f\n", *res_float);
    free(res_float);

    struct point_t p1; p1.x = 10; p1.y = 20;
    struct point_t p2; p2.x = 15; p2.y = -7;
    add = add_point;
    struct point_t* res_point = add(&p1, &p2);
    printf("%d %d\n", res_point->x, res_point->y);
    free(res_point);

    return 0;
}
