#include <stdio.h>
#include <stdlib.h>

int* create_number(int value) {
    int* num;
    num = malloc(sizeof(int));
    if (num == NULL) {
        return NULL;
    }
    *num = value;

    return num;
}

int main() {
    int* num = create_number(10);
    if (num == NULL) {
        return 1;
    }
    printf("%d\n", *num);
    free(num);
    return 0;
}
