#include <stdio.h>

int main() {
    char file_name[31] = "input.txt\0";
    FILE* f = fopen(file_name, "r");
    if (f == NULL) {
        printf("cannot open file\n");
        return 1;
    }

    int number_from_file;
    int numbers_in_file = 0;
    int has_to_be_numbers_in_file = 10;
    while (fscanf(f, "%d", &number_from_file) == 1) {
        numbers_in_file++;
    }
    if (numbers_in_file != has_to_be_numbers_in_file) {
        printf("corrupted\n");
        return 1;
    }
    if (!feof(f)) {
        printf("corrupted\n");
        return 1;
    }

    printf("all is ok!\n");
    fclose(f);

    return 0;
}
