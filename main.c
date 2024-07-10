#include <stdio.h>
#include <stdlib.h>

int accept_pointer(char* some_pointer) {
    if (some_pointer == NULL) {
        return -1;
    }
    return 0;
}

int main() {
    int res;
    res = accept_pointer(NULL);
    if (res == -1) {
        printf("invalid data");
    }
    char* ch = malloc(1);
    res = accept_pointer(ch);
    if (res == -1) {
        printf("invalid data");
    }

    return 0;
}