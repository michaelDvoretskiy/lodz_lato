#include <stdio.h>
#include <stdlib.h>

struct point_t {
    int x;
    int y;
};

int validate_point_with_message(struct point_t* p) {
    if (p == NULL) {
        printf("incorrect input\n");
        return 1;
    }

    if (p->x < 0 || p->x > 100 || p->y < 0 || p->y > 100) {
        printf("incorrect input data\n");
        return 1;
    }

    return 0;
}

int validate_point_without_message(struct point_t* p) {
    if (p == NULL) {
        return 1;
    }

    if (p->x < 0 || p->x > 100 || p->y < 0 || p->y > 100) {
        return 2;
    }

    return 0;
}

int main() {
    struct point_t* p1 = malloc(sizeof(struct point_t));
    p1->x = 10; p1->y = 20;
    if (validate_point_with_message(p1) == 0) {
        printf("x=%d, y=%d\n", p1->x, p1->y);
    }

    p1->x = -10; p1->y = 200;
    if (validate_point_with_message(p1) == 0) {
        printf("x=%d, y=%d\n", p1->x, p1->y);
    }

    validate_point_with_message(NULL);

    int res = validate_point_without_message(p1);
    if (res == 0) {
        printf("x=%d, y=%d\n", p1->x, p1->y);
    } else if (res == 1) {
        printf("incorrect input\n");
    } else if (res == 2) {
        printf("incorrect input data\n");
    }
    return 0;
}
