#include <stdio.h>
#include <stdlib.h>

int main() {
    char file_name[31];
    printf("Enter file name to read:\n");
    scanf("%30s", file_name);

    FILE* my_file = fopen(file_name, "r");
    if (my_file == NULL) {
        printf("no such file %s\n", file_name);
    } else {
        printf("file %s was opened successfully\n", file_name);
        fclose(my_file);
    }


    char* file_name2 = malloc(31);
    if (file_name2 == NULL) {
        printf("Couldn't allocate memory\n");
        return 1;
    }

    printf("Enter file name to create:\n");
    scanf("%30s", file_name2);

    FILE* my_file2 = fopen(file_name2, "w");
    if (my_file2 == NULL) {
        printf("cannot create file %s\n", file_name2);
    } else {
        printf("file %s was created successfully\n", file_name);
        fclose(my_file2);
    }
    free(file_name2);

    return 0;
}
