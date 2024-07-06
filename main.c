#include <stdio.h>
#include <stdlib.h>

int main() {
    char* file_name = malloc(31);
    printf("Enter name:\n");
    scanf("%30s", file_name);

    // it is important to open file as binary, if open it like plain text using "r"
    // not all bytes will be read
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Couldn't open file");
        return 4;
    }

    // first approach - using "fgetc"
    long file_size = 0;
    while (fgetc(file) != EOF ) {
        file_size++;
    }

    printf("Filesize: %ld\n", file_size);

    // second approach - using "seek" and "ftell"
    fseek(file, 0, SEEK_END); // Move the file pointer to the end of the file
    file_size = ftell(file);  // Get the current position of the file pointer
    printf("Filesize: %ld\n", file_size);

    fclose(file);

    return 0;
}