#include <stdio.h>
#include <ctype.h>

int main() {
    char file_name[31] = "input.txt\0";
    FILE* f = fopen(file_name, "r");
    if (f == NULL) {
        printf("Couldn't open file %s\n", file_name);
        return 1;
    }

    // count all symbols in the file
    int symbols_quantity_in_file = 0;
    while (fgetc(f) != EOF) {
        symbols_quantity_in_file++;
    }

    rewind(f);

    // check if first line has only numbers and spaces
    // and count symbols in the first line
    int first_line_symbols_quantity = 0;
    char ch = fgetc(f);
    while (ch != '\n' && ch != '\r' && ch != EOF) {
        first_line_symbols_quantity++;

        if (!isdigit(ch) && ch != ' ') {
            printf("File %s is corrupted. First line contains unacceptable symbols", file_name);
        }

        ch = fgetc(f);
    }

    rewind(f);

    // read all numbers from the first line and check each of them
    int number_from_file = 0;
    for (int i = 0; i < first_line_symbols_quantity; i++) {
        ch = fgetc(f);
        if (isdigit(ch)) {
            number_from_file = number_from_file * 10 + (ch - '0');
        } else {
            if (number_from_file <= first_line_symbols_quantity || number_from_file > symbols_quantity_in_file) {
                printf("File %s is corrupted. Index %d is incorrect", file_name, number_from_file);
            }
            number_from_file = 0;
        }
    }

    fclose(f);

    return 0;
}
