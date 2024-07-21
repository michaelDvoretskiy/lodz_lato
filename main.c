#include <stdio.h>
#include <string.h>

union my_test_u {
    int i;
    float f;
    char s[10];
};

void show(union my_test_u u) {
    printf("int: %d, float %f, string %s\n", u.i, u.f, u.s);
}

int main() {
    union my_test_u u;
    u.i = 10;
    show(u);
    u.f = 15.23f;
    show(u);
    strcpy(u.s, "Hello");
    show(u);

    return 0;
}
