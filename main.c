#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    char file_name[31] = "input.txt\0";
    FILE* f = fopen(file_name, "r");
    if (f == NULL) {
        printf("cannot open file\n");
        return 1;
    }

    // first approach - read all the line, but we give 100 characters to it
    char line_from_file[100];
    if (fgets(line_from_file, sizeof(line_from_file), f) != NULL) {
        char* end_ptr;
        int first_line_number = strtol(line_from_file, &end_ptr, 10);
        if (*end_ptr != '\0' && *end_ptr != '\r' && *end_ptr != '\n') {
            printf("corrupted 1\n");
            return 1;
        }
        printf("%d\n", first_line_number);
    } else {
        printf("Error while reading the first line from file");
    }

    rewind(f);

    // second approach - read symbols one by one, memory is given only for 1 symbol
    char ch;
    int first_line_number2 = 0;

    ch = fgetc(f);
    while (ch != '\r' && ch != '\n' && ch != EOF) {
        if (isdigit(ch)) {
            first_line_number2 = first_line_number2 * 10 + (ch - '0');
        } else {
            printf("corrupted 2\n");
            return 1;
        }

        ch = fgetc(f);
    }
    printf("%d\n", first_line_number2);

    fclose(f);

    return 0;
}
