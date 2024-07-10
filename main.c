#include <stdio.h>
#include <ctype.h>

int main() {
    char file_name[31] = "input.txt\0";
    FILE* f_for_first_line = fopen(file_name, "r");
    if (f_for_first_line == NULL) {
        printf("Couldn't open file");
        return 1;
    }

    int number_from_first_line = 0;

    char ch;
    do {
        ch = fgetc(f_for_first_line);

        if (isdigit(ch)) {
            number_from_first_line = 10 * number_from_first_line + (ch - '0');
        } else {
            if (number_from_first_line != 0) {

                FILE* f_for_read_symbol = fopen(file_name, "r");
                if (f_for_read_symbol == NULL) {
                    printf("Couldn't open file");
                    fclose(f_for_first_line);
                    return 1;
                }
                char chr_from_file;
                for (int i = 0; i < number_from_first_line; i++) {
                    chr_from_file = fgetc(f_for_read_symbol);
                }
                printf("%d %c\n", number_from_first_line, chr_from_file);
                fclose(f_for_read_symbol);
            }
            number_from_first_line = 0;
        }
    } while (ch != '\r' && ch != '\n' && ch != EOF);
    fclose(f_for_first_line);
    return 0;
}
