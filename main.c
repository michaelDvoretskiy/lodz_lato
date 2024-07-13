#include <stdio.h>

char* string_trim(char* word) {
    int current_character = 0;

    while ( *(word + current_character) == ' ') {
        current_character++;
    }
    int start = current_character;

    int end = start;
    while ( *(word + current_character) != '\0') {
        if ( *(word + current_character) != ' ') {
            end = current_character;
        }
        current_character++;
    }
    *(word + end + 1) = '\0';

    return word + start;
}



int main() {
    char input[20] = "  Start and end  \0";
    printf("-%s-\n", string_trim(input));
    char input2[20] = "Start    \0";
    printf("-%s-\n", string_trim(input2));
    char input3[20] = "   end\0";
    printf("-%s-\n", string_trim(input3));
//    printf("Enter data:\n");
//    read();

    return 0;
}
