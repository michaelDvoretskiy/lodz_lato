#include <stdio.h>

int main() {
    char message[31] = "Hello world\0";

    int i = 0;
    // with []
    printf("The message is: ");
    while (message[i] != '\0') {
        printf("%c", message[i]);
        i++;
    }
    printf("\n");

    // without []
    printf("The message is: ");
    i = 0;
    while (*(message+i) != '\0') {
        printf("%c", *(message+i));
        i++;
    }

    return 0;
}
