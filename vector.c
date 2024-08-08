#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define CAPACITY_STEP 10

struct my_vector_t* create(int capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    struct my_vector_t* v = malloc(sizeof(struct my_vector_t));
    if (v == NULL) {
        return NULL;
    }
    v->capacity = capacity;
    v->size = 0;
    v->data = malloc(sizeof(int)*capacity);

    return v;
}

int increase_size(struct my_vector_t* v) {
    if (v == 0) {
        return 1;
    }
    struct my_vector_t* new_v = realloc(v, v->capacity + CAPACITY_STEP);
    if (new_v == NULL) {
        return 2;
    }
    v = new_v;
    v->capacity += CAPACITY_STEP;

    return 0;
}

int decrease_size(struct my_vector_t* v) {
    if (v == NULL) {
        return 1;
    }

    if (v->capacity < CAPACITY_STEP) {
        return 0;
    }

    struct my_vector_t* new_v = realloc(v, v->capacity - CAPACITY_STEP);
    if (new_v == NULL) {
        return 1;
    }
    v = new_v;
    v->capacity -= CAPACITY_STEP;

    return 0;
}

void show(struct my_vector_t* v) {
    if (v == NULL) {
        return;
    }
    printf("Size: %d, capacity: %d\n", v->size, v->capacity);
    for (int i = 0; i < v->size; i++) {
        printf("%d ", *(v->data + i));
    }
    printf("\n");
    printf("================\n");
}

void destroy(struct my_vector_t* v) {
    if (v == NULL) {
        return;
    }
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

int add(struct my_vector_t* v, int value) {
    if (v == NULL || v->data == NULL) {
        return 1;
    }

    if (v->size == v->capacity) {
        int res = increase_size(v);
        if (res != 0) {
            return 2;
        }
    }
    *(v->data + v->size) = value;
    v->size++;

    return 0;
}

int rem_by_index(struct my_vector_t* v, int index) {
    if (v == NULL || v->data == NULL) {
        return 1;
    }
    if (index < 0 || index >= v->size) {
        return 2;
    }

    for (int i = index; i < v->size - 1; i++) {
        *(v->data + i) = *(v->data + i +1);
    }
    v->size--;

    if (v->capacity - v->size >= CAPACITY_STEP) {
        int operation_res = decrease_size(v);
        if (operation_res != 0) {
            return 3;
        }
    }

    return 0;
}

int rem_all_by_value(struct my_vector_t* v, int value) {
    if (v == NULL || v->data == NULL) {
        return 1;
    }
    for (int i = 0; i < v->size; i++) {
        if (*(v->data + i) == value) {
            int operation_res = rem_by_index(v, i);
            if (operation_res != 0) {
                return 2;
            }
        }
    }

    return 0;
}

int get(struct my_vector_t* v, int index, int* value) {
    if (v == NULL || value == NULL || v->data == NULL) {
        return 1;
    }
    if (index < 0 || index >= v->size) {
        return 1;
    }

    *value = *(v->data + index);

    return 0;
}

int set(struct my_vector_t* v, int index, int value) {
    if (v == NULL || v->data == NULL) {
        return 1;
    }
    if (index < 0 || index >= v->size) {
        return 1;
    }

    *(v->data + index) = value;

    return 0;
}