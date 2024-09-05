#include <stdio.h>
#include "list.h"
#include <stdlib.h>

int main() {
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("cannot open file\n");
        return 1;
    }

    struct header_t* head = malloc(sizeof(struct header_t));
    if (read_header(head, f) != 0) {
        return 1;
    }
    show_header(head);

    free_header(head);

    fclose(f);
    return 0;
}
