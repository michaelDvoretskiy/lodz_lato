#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main() {
    char file_name[31];
    printf("Enter name:\n");
    int scan_res = scanf("%30s", file_name);
    if (scan_res != 1) {
        printf("smth went wrong!\n");
        return 1;
    }

    FILE* f = fopen(file_name, "r");
    if (f == NULL) {
        printf("smth went wrong!\n");
        return 1;
    }

    char* string_from_file = malloc(MAX_LINE_LENGTH);
    while (fgets(string_from_file, MAX_LINE_LENGTH, f) != NULL) {
        printf("String: %s\n", string_from_file);
        char* sub_string_from_file = strtok(string_from_file, " \n");
        while(sub_string_from_file != NULL) {
            printf("Substring: %s\n", sub_string_from_file);
            sub_string_from_file = strtok(NULL, " \n");
        }
        printf("================\n");
    }

    fclose(f);

    return 0;
}
