#include <stdio.h>

struct point_t {
    int x;
    int y;
};

int main() {
    struct point_t p1;

    p1.x = 10;
    p1.y = 20;

    // p2 - незалежна структура,
    // зміни у ній не впливають на p1
    struct point_t p2 = p1;
    p2.x = 1;

    // p3 - посилання (вказівник) на структуру p1
    // тому зміни у p1 впливають на p3 і навпаки
    // фактично це одна і та сама структура
    struct point_t* p3 = &p1;
    p3->x = 100;
    p1.y = 200;

    printf("p1 x=%d, y=%d\n", p1.x, p1.y);
    printf("p2 x=%d, y=%d\n", p2.x, p2.y);
    printf("p3 x=%d, y=%d\n", p3->x, p3->y);
    return 0;
}
