#include <stdio.h>
#include "functions.h"

int add(int x, int y) {
    return x + y;
}

int sub(int x, int y) {
    return x - y;
}

void show(int x) {
    printf("%d\n", x);
}

void show2(int x) {
    printf("===========\n");
    printf("The result is: %d\n", x);
    printf("===========\n");
}