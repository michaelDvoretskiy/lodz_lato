#include <stdio.h>
#include <stdlib.h>


char* read_string(int start_len, int step) {
    int cur_str_len = start_len;
    char* str = malloc(sizeof(char) * (cur_str_len + 1));
    if (str == NULL) {
        printf("Input error");
        return NULL;
    }

    printf("Enter string:\n");
    char chr;
    if (scanf("%c", &chr) != 1) {
        printf("Input error");
        return NULL;
    }
    int i = 0;
    while (chr != '\n') {
        if (i >= cur_str_len) {
            cur_str_len += step;
            char* new_str = realloc(str, sizeof(char) * (cur_str_len + 1));
            if (new_str == NULL) {
                printf("Input error");
                return NULL;
            }
            str = new_str;
        }
        *(str + i) = chr;
        i++;
        if (scanf("%c", &chr) != 1) {
            printf("Input error");
            return NULL;
        }
    }
    *(str + i) = '\0';

    return str;
}


int main() {
    char* input = read_string(5, 3);
    printf("You entered : %s\n", input);
    free(input);

    return 0;
}
