#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue_t* create_queue(int capacity) {
    if (capacity < 1) {
        return NULL;
    }

    struct queue_t* q = malloc(sizeof(struct queue_t));
    if (q == NULL) {
        return NULL;
    }

    q->ptr = malloc(sizeof(int) * capacity);
    if (q->ptr == NULL) {
        free(q);
        return NULL;
    }

    q->begin = -1;
    q->end = -1;
    q->capacity = capacity;
    q->full = 0;

    return q;
}

void destroy_queue(struct queue_t* q) {
    if (q == NULL) {
        return;
    }

    if (q->ptr != NULL) {
        free(q->ptr);
    }
    free(q);
}

void push_to_queue(struct queue_t* q, int num, int* status) {
    if (q == NULL || q->ptr == NULL) {
        if (status != NULL) {
            *status = 1;
        }
        return;
    }

    if (q->full == 1) {
        if (status != NULL) {
            *status = 2;
        }
        return;
    }

    if (q->begin == -1) {
        q->begin = 0;
    }
    q->end++;
    if (q->end == q->capacity) {
        q->end = 0;
    }
    *(q->ptr + q->end) = num;

    if (q->begin == 0 && q->end == (q->capacity - 1)) {
        q->full = 1;
    } else if (q->begin - q->end == 1) {
        q->full = 1;
    }

    if (status != NULL) {
        *status = 0;
    }
}

int pop_from_queue(struct queue_t* q, int* status) {
    if (q == NULL || q->ptr == NULL) {
        if (status != NULL) {
            *status = 1;
        }
        return 0;
    }


    int res = *(q->ptr + q->begin);

    if (q->begin == q->end) {
        q->begin = -1;
        q->end = -1;
    } else {
        q->begin++;
        if (q->begin == q->capacity) {
            q->begin = 0;
        }
    }
    q->full = 0;

    return res;
}

void show_queue(struct queue_t* q) {
    if (q == NULL || q->ptr == NULL) {
        return;
    }

    if (q->begin == -1) {
        return;
    }

    printf("begin = %d, end = %d, full = %d, capacity = %d\n", q->begin, q->end, q->full, q->capacity);
    int i = q->begin;
    printf("%d ", *(q->ptr + i));
    while (i != q->end) {
        i++;
        if (i >= q->capacity) {
            i = 0;
        }
        printf("%d ", *(q->ptr + i));
    }
    printf("\n");
}