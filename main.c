#include <stdio.h>
#include <stdlib.h>

char* read_string(int max_len) {
    char* str = malloc(sizeof(char) * (max_len + 1));

    printf("Enter string:\n");
    char chr;
    if (scanf("%c", &chr) != 1) {
        printf("Input error");
        return NULL;
    }
    int i = 0;
    while (chr != '\n') {
        if (i < max_len) {
            *(str + i) = chr;
            i++;
        }
        if (scanf("%c", &chr) != 1) {
            printf("Input error");
            return NULL;
        }
    }
    *(str + i) = '\0';

    return str;
}

int main() {
    char* input = read_string(20);
    printf("You entered : %s\n", input);
    free(input);

    return 0;
}
