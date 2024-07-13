#include <stdio.h>

struct point_t {
    int x;
    int y;
};

int main() {
    struct point_t p1, p2;
    p1.x = 10;
    p1.y = 20;
    p2 = p1;

    // подальші зміни полів  однієї структури
    // не впливають на дані іншої структури
    p2.x = 1;
    p1.y = 2;
    printf("p1 x=%d, y=%d\n", p1.x, p1.y);
    printf("p2 x=%d, y=%d\n", p2.x, p2.y);
    return 0;
}
