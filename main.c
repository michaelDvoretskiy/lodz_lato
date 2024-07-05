#include <stdio.h>
#include <stdlib.h>

int main() {
    char* file_name = malloc(31);
    printf("Enter name:\n");
    scanf("%30s", file_name);

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Couldn't open file\n");
        return 4;
    }

    int chr;
    int is_empty = 1;
    while ((chr = fgetc(file)) != EOF) {
        is_empty = 0;
        printf("%c", chr);
    }

    if (is_empty) {
        printf("Nothing to show\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 0;
}
