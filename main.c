#include <stdio.h>
#include <stdlib.h>

struct point_t {
    int x;
    int y;
};

int add_int(int x, int y) {
    return x + y;
}

float add_float(float x, float y) {
    return x + y;
}

struct point_t* add_point(struct point_t* p1, struct point_t* p2) {
    struct point_t* new_point = malloc(sizeof(struct point_t));
    new_point->x = p1->x + p2->x;
    new_point->y = p1->y + p2->y;

    return new_point;
}

int main() {
    int (*add)(int, int);
    add = add_int;
    printf("%d\n", add(10, 20));

    // дальнейшая проблема в том, что мы теперь не можем использовать указатель add
    // чтобы записать туда add_float или add_point т.к. у них разный тип (разная сигнатура)
    // add_int - int (int, int)
    // add_float - float (float, float)
    // add_point - struct point_t* (struct point_t*, struct point_t*)

    // нужно создавать новые переменные-указатели для float и point
    // и работать через них
    float (*add2)(float, float) = add_float;
    printf("%f\n", add2(10.5f, 2.05f));

    struct point_t* (*add3)(struct point_t*, struct point_t*) = add_point;
    struct point_t p1; p1.x = 10; p1.y = 20;
    struct point_t p2; p2.x = 15; p2.y = -7;
    struct point_t* p = add3(&p1, &p2);
    printf("%d %d\n", p->x, p->y);

    // но тогда вопрос, на кой нам тут указатели add, add2 и add3,
    // если можно просто так
    printf("%d\n", add_int(10, 20));
    printf("%f\n", add_float(10.5f, 2.05f));
    struct point_t* pp = add_point(&p1, &p2);
    printf("%d %d\n", pp->x, pp->y);

    // было бы удобно создать такой указатель add, чтобы туда в зависимости от того,
    // с каким типом мы выберем работать, передать add_int, add_float или add_point
    // и работать потом с ним
    // но мы не можем этого сделать, пока у add_int, add_float или add_point разные сигнатуры

    return 0;
}
