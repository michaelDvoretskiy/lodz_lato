#include <stdio.h>

int main() {
    char file_name[31];
    printf("Enter name:\n");
    scanf("%30s", file_name);

    printf("You entered: %s", file_name);
    return 0;
}
