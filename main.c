#include <stdio.h>

int main() {
    char file_name[31];
    printf("Enter name:\n");

    int i = 0;
    char c;
    scanf("%c", &c);
    while (c != '\n') {
        file_name[i] = c;
        // or *(file_name + i) = c;
        scanf("%c", &c);
        i++;
    }
    file_name[i] = '\0';
    // or *(file_name + i) = '\0';

    printf("You entered: %s", file_name);
    return 0;
}
