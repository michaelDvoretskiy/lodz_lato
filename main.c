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
                printf("%s\n", word);
                free(word);
            }
        }
    }

    fclose(f);
    return 0;
}
