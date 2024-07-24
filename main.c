#include <stdio.h>
#include <stdlib.h>

struct point_t {
    int x;
    int y;
};

struct circle_t {
    struct point_t center;
    int radius;
};

struct triangle_t {
    struct point_t A;
    struct point_t B;
    struct point_t C;
};

enum figure_types {
    CIRCLE = 1,
    TRIANGLE = 2
};

struct figure_t {
    enum figure_types type;
    union {
        struct triangle_t triangle;
        struct circle_t circle;
    };
};

void display_triangle(struct triangle_t* triangle) {
    printf("Triangle. A(%d %d), B(%d %d), C(%d %d)\n",
           triangle->A.x, triangle->A.y, triangle->B.x, triangle->B.y, triangle->C.x, triangle->C.y);
}

void display_circle(struct circle_t* circle) {
    printf("Circle. O(%d %d), R(%d)\n",
           circle->center.x, circle->center.y, circle->radius);
}

void display_figure(struct figure_t* f) {
    if (f->type == CIRCLE) {
        display_circle(&(f->circle));
    } else if (f->type == TRIANGLE) {
        display_triangle(&(f->triangle));
    }
}

int main() {
    // создаем структуру (не как указатель)
    struct figure_t f1;
    f1.type = CIRCLE;
    f1.circle.center.x = 10;
    f1.circle.center.y = 20;
    f1.circle.radius = 5;
    // отображаем окружность как фигуру
    display_figure(&f1);
    // отображаем окружность из фигуры как окружность
    display_circle(&(f1.circle));

    // отображаем треугольник из фигуры, в которой хранится окружность, для прикола ;)
    display_triangle(&(f1.triangle));
    // говорим, что фигура - треугольник, хотя по факту там хранится окружность, тоже для прикола ;)
    f1.type = TRIANGLE;
    // и теперь отображаем эту фигуру (треугольник), в которой по факту хранится окружность
    display_figure(&f1);

    printf("========================\n");

    // создаем структуру, как указатель
    struct figure_t* f2_p = malloc(sizeof(struct figure_t));
    if (f2_p == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    f2_p->type = TRIANGLE;
    f2_p->triangle.A.x = 1;
    f2_p->triangle.A.y = 2;
    f2_p->triangle.B.x = 3;
    f2_p->triangle.B.y = 4;
    f2_p->triangle.C.x = 5;
    f2_p->triangle.C.y = 6;
    display_figure(f2_p);

    // выводим треугольник, как окружность
    display_circle(&(f2_p->circle));

    free(f2_p);

    printf("========================\n");

    // создаем массив из 2-х фигур (элементом массива будет сама структура "фигура", а не указатель на фигуру)
    struct figure_t* f_arr = malloc(sizeof(struct figure_t) * 2);
    if (f_arr == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    // инициализируем первый элемент массивва
    f_arr->type = CIRCLE;
    f_arr->circle.center.x = 8;
    f_arr->circle.center.y = 12;
    f_arr->circle.radius = 7;
    // инициализируем второй элемент массивва
    (f_arr+1)->type = TRIANGLE;
    (f_arr+1)->triangle.A.x = 10;
    (f_arr+1)->triangle.A.y = 20;
    (f_arr+1)->triangle.B.x = 30;
    (f_arr+1)->triangle.B.y = 40;
    (f_arr+1)->triangle.C.x = 50;
    (f_arr+1)->triangle.C.y = 60;

    for (int i = 0; i < 2; i++) {
        display_figure((f_arr+i));
    }
    free(f_arr);

    printf("========================\n");

    // создаем массив из 2-х указателей на фигуры (элементом массива будет указатель на фигуру)
    struct figure_t** f_arr_p = malloc(sizeof(struct figure_t*) * 2);
    if (f_arr_p == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    // инициализируем первый элемент массивва
    *f_arr_p = malloc(sizeof(struct figure_t));
    if (*f_arr_p == NULL) {
        free(f_arr_p);
        printf("Failed to allocate memory\n");
        return 1;
    }
    (*f_arr_p)->type = CIRCLE;
    (*f_arr_p)->circle.center.x = 80;
    (*f_arr_p)->circle.center.y = 21;
    (*f_arr_p)->circle.radius = 15;
    // инициализируем второй элемент массивва
    *(f_arr_p+1) = malloc(sizeof(struct figure_t));
    if (*(f_arr_p+1) == NULL) {
        free(*f_arr_p);
        free(f_arr_p);
        printf("Failed to allocate memory\n");
        return 1;
    }
    (*(f_arr_p+1))->type = TRIANGLE;
    (*(f_arr_p+1))->triangle.A.x = 15;
    (*(f_arr_p+1))->triangle.A.y = 25;
    (*(f_arr_p+1))->triangle.B.x = 35;
    (*(f_arr_p+1))->triangle.B.y = 45;
    (*(f_arr_p+1))->triangle.C.x = 55;
    (*(f_arr_p+1))->triangle.C.y = 65;

    for (int i = 0; i < 2; i++) {
        display_figure(*(f_arr_p+i));
    }

    // чистим память каждого єлемента массива
    for (int i = 0; i < 2; i++) {
        free(*(f_arr_p+i));
    }
    // чистим память всего массива
    free(f_arr_p);

    return 0;
}
