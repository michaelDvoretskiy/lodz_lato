#include <stdio.h>

struct point_t {
    int x;
    int y;
};

struct point_t* set_values(struct point_t* p, int x, int y) {
    p->x = x;
    p->y = y;

    return p;
}

int main() {
    struct point_t p1;
    struct point_t* p2 = set_values(&p1, 5, 6);
    // p2 буде вказівником на p1, фактично це одна і та ж структура
    printf("x=%d, y=%d\n", p1.x, p1.y);
    printf("x=%d, y=%d\n", p2->x, p2->y);
    return 0;
}
