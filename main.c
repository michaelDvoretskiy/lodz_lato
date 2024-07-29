#include <stdio.h>
#include <stdlib.h>


int main() {
    int* num;
    num = malloc(sizeof(int));
    if (num == NULL) {
        return 1;
    }
    *num = 10;
    printf("%d\n", *num);
    free(num);
    return 0;
}
