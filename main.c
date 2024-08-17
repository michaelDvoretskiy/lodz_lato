#include <stdio.h>
#include <stdlib.h>

int read_string(char** str, int max_len) {
    *str = malloc(sizeof(char) * (max_len + 1));

    printf("Enter string:\n");
    char chr;
    if (scanf("%c", &chr) != 1) {
        printf("Input error");
        return NULL;
    }
    int i = 0;
    while (chr != '\n') {
        if (i < max_len) {
            *(*str + i) = chr;
            i++;
        }
        if (scanf("%c", &chr) != 1) {
            printf("Input error");
            return 1;
        }
    }
    *(*str + i) = '\0';

    return 0;
}

int main() {
    char* input;
    if (read_string(&input, 20)) {
        return 1;
    }
    printf("You entered : %s\n", input);
    free(input);

    return 0;
}
