#include <stdio.h>

int main() {
    char message[31] = "Hello world\0";

    printf("The message is: %s", message);
    return 0;
}
