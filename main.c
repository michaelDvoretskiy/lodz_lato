#include "functions.h"

int main() {
    int (*operation)(int, int);
    operation = sub;

    void (*shower)(int) = show2;

    int res = operation(5, 10);
    shower(res);

    operation = add;
    shower = show;
    shower(operation(3, 5));

    return 0;
}
