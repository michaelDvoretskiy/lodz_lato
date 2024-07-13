#include <stdio.h>

struct point_t {
    int x;
    int y;
};

void show_point(struct point_t* p) {
    printf("Point info\n");
    printf("x = %d, y = %d", p->x, p->y);
}

int main() {
    struct point_t p1;
    p1.x = 10;
    p1.y = 20;
    show_point(&p1);

    return 0;
}
