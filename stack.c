#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int stack_init(struct stack_t **stack) {
    if (stack == NULL) {
        return 1;
    }

    *stack = malloc(sizeof(struct stack_t));
    if (*stack == NULL) {
        return 2;
    }

    (*stack)->head = NULL;

    return 0;
}

int stack_push(struct stack_t *stack, int value) {
    if (stack == NULL) {
        return 1;
    }

    struct node_t* new_node = malloc(sizeof(struct node_t));
    if (new_node == NULL) {
        return 2;
    }

    new_node->data = value;
    new_node->next = stack->head;

    stack->head = new_node;

    return 0;
}

void stack_display(const struct stack_t* stack) {
    if (stack == NULL) {
        return;
    }

    struct node_t* current = stack->head;
    if (current == NULL) {
        return;
    }

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int stack_pop(struct stack_t* stack, int *err_code) {
    if (stack == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return -1;
    }
    if (stack->head == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return -1;
    }

    struct node_t* temp = stack->head;
    int value = temp->data;
    stack->head = stack->head->next;
    free(temp);

    if (err_code != NULL) {
        *err_code = 0;
    }
    return value;
}

void stack_free(struct stack_t** stack) {
    if (stack == NULL || *stack == NULL) {
        return;
    }
    struct node_t* current = (*stack)->head;
    while (current != NULL) {
        struct node_t* next = current->next;
        free(current);
        current = next;
    }
    free(*stack);
    *stack = NULL;
}