#include <stdio.h>
#include <stdlib.h>

int read_string(char** str) {
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        return 1;
    }

    int symbols_in_file = 0;
    while (!feof(f)) {
        fgetc(f);
        symbols_in_file++;
    }

    *str = malloc(sizeof(char) * (symbols_in_file + 1));
    if (*str == NULL) {
        return 2;
    }

    rewind(f);

    for(int i = 0; i< symbols_in_file; i++) {
        *(*str + i) = fgetc(f);
    }

    *(*str + symbols_in_file) = '\0';

    return 0;
}

int main() {
    char* input;
    if (read_string(&input) != 0) {
        return 1;
    }
    printf("We read from file:\n%s\n", input);
    free(input);

    return 0;
}
