#include <stdio.h>
#include "queue.h"

int main() {
    int status;
    struct queue_t* q = create_queue(3);
    if (q == NULL) {
        return 1;
    }
    // добавляем 4 числа
    for (int i = 1; i < 5; i++) {
        printf("Add %d\n", i);
        push_to_queue(q, i, &status);
        printf("status = %d\n", status);
        show_queue(q);
        printf("============\n");
    }

    // убираем 2 числа
    for (int i = 1; i < 3; i++) {
        printf("Remove %d\n", i);
        int val = pop_from_queue(q, &status);
        printf("status = %d\n", status);
        if (status == 0) {
            printf("value = %d\n", val);
        }
        show_queue(q);
        printf("============\n");
    }

    // добавляем 2 числа
    for (int i = 1; i < 4; i++) {
        printf("Add %d\n", i);
        push_to_queue(q, i, &status);
        printf("status = %d\n", status);
        show_queue(q);
        printf("============\n");
    }

    // убираем 4 числа
    for (int i = 1; i < 5; i++) {
        printf("Remove %d\n", i);
        int val = pop_from_queue(q, &status);
        printf("status = %d\n", status);
        if (status == 0) {
            printf("value = %d\n", val);
        }
        show_queue(q);
        printf("============\n");
    }

    destroy_queue(q);

    return 0;
}
