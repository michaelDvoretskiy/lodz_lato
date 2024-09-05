#include <stdio.h>
#include "list.h"
#include <stdlib.h>

int main() {
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("cannot open file\n");
        return 1;
    }

    char buf[1024];
    while (!feof(f)) {
        int status = read_line(f, buf);
        if (status != 0) {
            printf("cannot read the line\n");
            return 1;
        }
        printf("%s\n", buf);

        int words_count = count_words(buf);
        printf("%d\n", words_count);
        for (int i = 0; i < words_count; i++) {
            char* word = get_word(buf, i);
            if (word != NULL) {
                printf("%s ", word);
                enum type_t word_type = get_type(word);
                if (word_type == INT) {
                    printf("integer\n");
                } else if (word_type == DBL) {
                    printf("double\n");
                } else if (word_type == STR) {
                    printf("string\n");
                }
                free(word);
            }
        }
    }

    fclose(f);
    return 0;
}
