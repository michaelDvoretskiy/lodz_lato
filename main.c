#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "my_strings.h"

int main() {
    int texts_number;
    if (read_number_of_texts(&texts_number) != 0) {
        return 1;
    }

    char** texts;
    if (create_texts(&texts, texts_number) != 0) {
        return 1;
    }

    if (read_texts(texts, texts_number) != 0) {
        destroy_texts(texts, texts_number);
        return 1;
    }

    display_texts(texts, texts_number);

    char* result;
    int concat_res = concat_texts(
            &result,
            texts_number,
            texts_number > 0 ? *(texts) : NULL,
            texts_number > 1 ? *(texts + 1) : NULL,
            texts_number > 2 ? *(texts + 2) : NULL,
            texts_number > 3 ? *(texts + 3) : NULL
    );
    if (concat_res != 0) {
        destroy_texts(texts, texts_number);
        return 1;
    }

    printf("%s\n", result);

    destroy_texts(texts, texts_number);
    free(result);

    return 0;
}