#ifndef CODE_STACK_H
#define CODE_STACK_H

struct node_t {
    int data;
    struct node_t* next;
};

struct stack_t {
    struct node_t *head;
};

int stack_init(struct stack_t** stack);
int stack_push(struct stack_t* stack, int value);
void stack_display(const struct stack_t* stack);
int stack_pop(struct stack_t* stack, int* err_code);
void stack_free(struct stack_t** stack);
int stack_empty(const struct stack_t* stack);

#endif //CODE_STACK_H
