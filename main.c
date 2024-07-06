#include <stdio.h>

int main() {
    int input;
    printf("Enter numbers:\n");
    while (scanf("%d", &input) == 1 && input != 0) {
        printf("%d\n", input);
    }
    return 0;
}
