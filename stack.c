
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int stack_init(struct stack_t** stack, int N) {
    if (stack == NULL || N <= 0) {
        return 1;
    }

    *stack = malloc(sizeof(struct stack_t));
    if (*stack == NULL) {
        return 2;
    }
    (*stack)->data = malloc(N * sizeof(int));
    if ((*stack)->data == NULL){
        free(*stack);
        *stack = NULL;
        return 2;
    }
    (*stack)->head = 0;
    (*stack)->capacity = N;

    return 0;
}

int give_more_memory(struct stack_t* stack) {
    int* new_data = realloc(stack->data, stack->capacity * 2 * sizeof(int));
    if (new_data == NULL) {
        return 1;
    }
    stack->data = new_data;
    stack->capacity *= 2;

    return 0;
}

int validate_stack(const struct stack_t* stack) {
    if (stack == NULL || stack->data == NULL || stack->head < 0 || stack->capacity <= 0 || stack->head > stack->capacity) {
        return 1;
    }

    return 0;
}

int stack_push(struct stack_t* stack, int value) {
    if (validate_stack(stack) != 0) {
        return 1;
    }
    if (stack->head == stack->capacity) {
        if (give_more_memory(stack) != 0) {
            return 2;
        }
    }
    *(stack->data + stack->head) = value;
    stack->head++;
    return 0;
}

int stack_pop(struct stack_t *stack, int *err_code) {
    if (validate_stack(stack) != 0) {
        if (err_code) {
            *err_code = 1;
        }
        return 0;
    }
    if (stack->head == 0) {
        if (err_code) {
            *err_code = 2;
        }
        return 0;
    }
    stack->head--;

    if (err_code) {
        *err_code = 0;
    }

    return *(stack->data + stack->head);
}

void stack_display(const struct stack_t* stack) {
    if (validate_stack(stack) != 0) {
        return;
    }
    printf("Capacity: %d, head: %d\n", stack->capacity, stack->head);
    printf("Stack content: ");
    for (int i = stack->head - 1; i >= 0; i--) {
        printf(" %d", *(stack->data + i));
    }
    printf("\n");
    printf("---------------------\n");
}

void stack_free(struct stack_t *stack) {
    if (stack != NULL) {
        free(stack->data);
        free(stack);
    }
}

