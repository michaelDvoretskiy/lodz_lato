#include <stdio.h>

struct point_t {
    int x;
    int y;
};

void set_values(struct point_t* p, int x, int y) {
    p->x = x;
    p->y = y;
}

int main() {
    struct point_t p1;
    set_values(&p1, 5, 6);
    printf("x=%d, y=%d", p1.x, p1.y);

    return 0;
}
