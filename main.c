#include <stdio.h>
#include <stdlib.h>

struct point_t {
    int x;
    int y;
};

struct circle_t {
    struct point_t* center;
    int radius;
};

struct triangle_t {
    struct point_t* A;
    struct point_t* B;
    struct point_t* C;
};

enum figure_types {
    CIRCLE = 1,
    TRIANGLE = 2
};

struct figure_t {
    enum figure_types type;
    union {
        struct triangle_t* triangle;
        struct circle_t* circle;
    };
};

void display_triangle(struct triangle_t* triangle) {
    printf("Triangle. A(%d %d), B(%d %d), C(%d %d)\n",
           triangle->A->x, triangle->A->y, triangle->B->x, triangle->B->y, triangle->C->x, triangle->C->y);
}

void display_circle(struct circle_t* circle) {
    printf("Circle. O(%d %d), R(%d)\n",
           circle->center->x, circle->center->y, circle->radius);
}

void display_figure(struct figure_t* f) {
    if (f->type == CIRCLE) {
        display_circle(f->circle);
    } else if (f->type == TRIANGLE) {
        display_triangle(f->triangle);
    }
}

struct figure_t* create_figure(enum figure_types type) {
    struct figure_t* f = malloc(sizeof(struct figure_t));
    if (f == NULL) {
        return NULL;
    }
    f->type = type;

    if (type == CIRCLE) {
        f->circle = malloc(sizeof(struct circle_t));
        if (f->circle == NULL) {
            free(f);
            return NULL;
        }

        f->circle->center = malloc(sizeof(struct point_t));
        if (f->circle->center == NULL) {
            free(f->circle);
            free(f);
            return NULL;
        }
    } else if (type == TRIANGLE) {
        f->triangle = malloc(sizeof(struct triangle_t));
        if (f->triangle == NULL) {
            free(f);
            return NULL;
        }

        f->triangle->A = malloc(sizeof(struct point_t));
        if (f->triangle->A == NULL) {
            free(f->triangle);
            free(f);
            return NULL;
        }
        f->triangle->B = malloc(sizeof(struct point_t));
        if (f->triangle->B == NULL) {
            free(f->triangle->A);
            free(f->triangle);
            free(f);
            return NULL;
        }
        f->triangle->C = malloc(sizeof(struct point_t));
        if (f->triangle->C == NULL) {
            free(f->triangle->A);
            free(f->triangle->B);
            free(f->triangle);
            free(f);
            return NULL;
        }
    }
    return f;
}

void delete_figure(struct figure_t* f) {
    if (f == NULL) {
        return;
    }
    if (f->type == CIRCLE) {
        free(f->circle->center);
        free(f->circle);
        free(f);
    } else if (f->type == TRIANGLE) {
        free(f->triangle->A);
        free(f->triangle->B);
        free(f->triangle->C);
        free(f->triangle);
        free(f);
    }
}

int main() {
    // создаем массив из 2-х указателей на фигуры (элементом массива будет указатель на фигуру)
    struct figure_t** f_arr_p = malloc(sizeof(struct figure_t*) * 2);
    if (f_arr_p == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    // инициализируем первый элемент массивва
    *f_arr_p = create_figure(CIRCLE);
    if (*f_arr_p == NULL) {
        free(f_arr_p);
        printf("Failed to allocate memory\n");
        return 1;
    }
    (*f_arr_p)->circle->center->x = 80;
    (*f_arr_p)->circle->center->y = 21;
    (*f_arr_p)->circle->radius = 15;

    // инициализируем второй элемент массивва
    *(f_arr_p+1) = create_figure(TRIANGLE);
    if (*(f_arr_p+1) == NULL) {
        delete_figure(*f_arr_p);
        free(f_arr_p);
        printf("Failed to allocate memory\n");
        return 1;
    }
    (*(f_arr_p+1))->type = TRIANGLE;
    (*(f_arr_p+1))->triangle->A->x = 15;
    (*(f_arr_p+1))->triangle->A->y = 25;
    (*(f_arr_p+1))->triangle->B->x = 35;
    (*(f_arr_p+1))->triangle->B->y = 45;
    (*(f_arr_p+1))->triangle->C->x = 55;
    (*(f_arr_p+1))->triangle->C->y = 65;

    for (int i = 0; i < 2; i++) {
        display_figure(*(f_arr_p+i));
    }

    // чистим память каждого єлемента массива
    for (int i = 0; i < 2; i++) {
        delete_figure(*(f_arr_p+i));
    }
    // чистим память всего массива
    free(f_arr_p);

    return 0;
}
