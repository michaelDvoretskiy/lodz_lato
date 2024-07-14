#include <stdio.h>
#include <ctype.h>

int isNumber(char* input) {
    int current_character_number = 0;
    while (*(input + current_character_number) != '\0') {
        if (!isdigit(*(input + current_character_number))) {
            return 0;
        }
        current_character_number++;
    }
    return 1;
}

int main() {
    char input[20];
    printf("Enter a string:");
    scanf("%30s", input);
    printf(isNumber(input) == 1 ? "it is a number" : "it is not a number");

    return 0;
}
