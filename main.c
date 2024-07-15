#include <stdio.h>
#include <string.h>

char* get_ext(char* filename) {
    int current_symbol_number = 0;
    int last_dot_position = -1;
    while (*(filename + current_symbol_number) != '\0') {
        if (*(filename + current_symbol_number) == '.') {
            last_dot_position = current_symbol_number;
        }
        current_symbol_number++;
    }
    if (last_dot_position == -1) {
        return NULL;
    }

    return filename + last_dot_position;
}


int main() {
    char filename[31] = "file.txt\0";
    char filename2[31] = "file\0";
    char filename3[31] = "file.txt.bin\0";

    // функція strrchr знаходить останнє входження символу у рядок
    char *extension = strrchr(filename, '.');
    printf("File extension: %s\n", extension);

    extension = strrchr(filename2, '.');
    printf("File extension: %s\n", extension);

    extension = strrchr(filename3, '.');
    printf("File extension: %s\n", extension);

    // використання власної функції, трохи більше мороки,
    // але можна налаштувати "під себе"
    // наприклад, можна змінити функцію, щоб для випадку file.txt.bin (дві крапки) була помилка
    extension = get_ext(filename2);
    if (extension != NULL) {
        printf("File extension: %s\n", extension);
    } else {
        printf("Error while getting an extension\n");
    }
    return 0;
}
