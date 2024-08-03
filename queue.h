#ifndef CODE_QUEUE_H
#define CODE_QUEUE_H

struct queue_t {
    int *ptr;
    int begin;
    int end;
    int capacity;
    unsigned char full;
};

struct queue_t* create_queue(int capacity);

void destroy_queue(struct queue_t* q);

void push_to_queue(struct queue_t* q, int num, int* status);

int pop_from_queue(struct queue_t* q, int* status);

void show_queue(struct queue_t* q);

#endif
