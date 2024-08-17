#include <stdio.h>
#include <stdlib.h>

int main() {
    int max_len = 20;
    char* str = malloc(sizeof(char) * (max_len + 1));

    printf("Enter string:\n");
    char chr;
    if (scanf("%c", &chr) != 1) {
        printf("Input error");
        return 1;
    }
    int i = 0;
    while (chr != '\n') {
        if (i < max_len) {
            *(str + i) = chr;
            i++;
        }
        if (scanf("%c", &chr) != 1) {
            printf("Intup error");
            return 1;
        }
    }
    *(str + i) = '\0';

    printf("You entered : %s\n", str);

    free(str);

    return 0;
}
