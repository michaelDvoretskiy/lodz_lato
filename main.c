#include <stdio.h>
#include "functions.h"

int main() {
    int (*operations[2])(int, int) = {add, sub};
    void (*showers[2])(int) = {show, show2};

    int operation_number;
    printf("Choose operation (0 - add, 1 - sub):");
    if (scanf("%d", &operation_number) != 1) {
        return 1;
    }
    if (operation_number != 0 && operation_number != 1) {
        return 1;
    }

    int x, y;
    printf("Enter two numbers:");
    if (scanf("%d %d", &x, &y) != 2) {
        return 1;
    }

    int show_type;
    printf("Choose how to display the result (0 - short, 1 - full):");
    if (scanf("%d", &show_type) != 1) {
        return 1;
    }
    if (show_type != 0 && show_type != 1) {
        return 1;
    }

    make_job(x, y, operations[operation_number], showers[show_type]);

    return 0;
}
