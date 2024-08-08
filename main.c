#include <stdio.h>
#include "vector.h"

int main() {
    int operation_res;
    struct my_vector_t* v = create(2);
    if (v == NULL) {
        return 1;
    }
    show(v);

    operation_res = add(v, 10);
    if (operation_res != 0) {
        destroy(v);
        return 1;
    }
    operation_res = add(v, 20);
    if (operation_res != 0) {
        destroy(v);
        return 1;
    }
    show(v);

    operation_res = add(v, 15);
    if (operation_res != 0) {
        destroy(v);
        return 1;
    }
    show(v);

    operation_res = rem_by_index(v, 1);
    if (operation_res != 0) {
        destroy(v);
        return 1;
    }
    show(v);

    int val;
    operation_res = get(v, 0, &val);
    if (operation_res != 0) {
        destroy(v);
        return 1;
    }
    printf("%d\n===\n", val);

    operation_res = set(v, 1, 100);
    if (operation_res != 0) {
        destroy(v);
        return 1;
    }
    show(v);

    operation_res = add(v, 10);
    if (operation_res != 0) {
        destroy(v);
        return 1;
    }
    show(v);

    operation_res = rem_all_by_value(v, 10);
    if (operation_res != 0) {
        destroy(v);
        return 1;
    }
    show(v);

    destroy(v);

    return 0;
}
