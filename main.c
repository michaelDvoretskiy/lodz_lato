#include <stdio.h>

void change_n_to_0(char* arr, int max_len) {
    int i = 0;
    while (*(arr+i) != '\r' && *(arr+i) != '\n' && i < max_len) {
        i++;
    }
    *(arr+i) = '\0';
}

int main() {
    char file_name[31] = "file1.txt\0";

    FILE* f = fopen(file_name, "r");
    if (f == NULL) {
        return 0;
    }

    char file_line[31];
    while (fgets(file_line, sizeof(file_line), f)) {
        change_n_to_0(file_line, 30);
        printf("%s\n", file_line);
    }

    fclose(f);

    return 0;
}