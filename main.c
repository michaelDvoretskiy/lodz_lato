#include <stdio.h>
#include "stack.h"

int main() {
    struct stack_t* my_stack;
    if (stack_init(&my_stack) != 0) {
        printf("failed to create stack");
        return 1;
    }
    for (int i = 0; i < 10; i++) {
        if (stack_push(my_stack, i) != 0) {
            printf("failed to push to stack");
            return 1;
        }
        stack_display(my_stack);
    }

    for (int i = 0; i < 3; i++) {
        int pop_status;
        int value = stack_pop(my_stack, &pop_status);
        if (pop_status == 0) {
            printf("popped last element %d\n", value);
        }
    }

    stack_display(my_stack);

    stack_free(&my_stack);

    return 0;
}
