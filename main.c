#include <stdio.h>

int main() {
    char file_name[31] = "input.txt\0";

    FILE* my_file = fopen(file_name, "r");
    int number_from_file;
    while (fscanf(my_file, "%d", &number_from_file) == 1) {
    }
    if (!feof(my_file)) {
        printf("File corrupted\n");
        return 1;
    }
    fclose(my_file);

    return 0;
}
