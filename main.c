#include <stdio.h>
#include <stdlib.h>

void set_value(int* number_pointer, int number_value) {
    if (number_pointer == NULL) {
        return;
    }
    *number_pointer = number_value;
}

void show_number(int* number_pointer) {
    printf("%d\n", *number_pointer);
}

int main() {
    int* num_p;
    num_p = malloc(sizeof(int));
    if (num_p == NULL) {
        return 1;
    }
    set_value(num_p, 10);
    show_number(num_p);
    free(num_p);

    int num_v;
    set_value(&num_v, 20);
    show_number(&num_v);

    return 0;
}
