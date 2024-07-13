#include <stdio.h>
#include <stdlib.h>

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
    struct point_t* p1 = malloc(sizeof(struct point_t));
    p1->x = 10;
    p1->y = 20;
    printf("x=%d, y=%d\n", p1->x, p1->y);
    p1 = set_values(p1, 1, 2);
    printf("x=%d, y=%d\n", p1->x, p1->y);
    return 0;
}
