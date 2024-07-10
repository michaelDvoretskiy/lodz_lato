#include <stdio.h>

int read_file(char* filename);

int main() {
    char file_name[31];
    printf("Enter name:\n");
    if (scanf("%30s", file_name) != 1) {
        printf("failed to read the filename\n");
        return 1;
    }

    int res = read_file(file_name);
    if (res != -1) {
        printf("File quantity %d", res);
    }

    return 0;
}

void change_n_to_0(char* arr, int max_len) {
    int i = 0;
    while (*(arr+i) != '\r' && *(arr+i) != '\n' && i < max_len) {
        i++;
    }
    *(arr+i) = '\0';
}

int read_file(char* filename) {
    int files_count = 0;
    if (filename == NULL) {
        return -1;
    }
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        return 0;
    }
    char inner_filename[31];
    while (fgets(inner_filename, sizeof(inner_filename), f)) {
        change_n_to_0(inner_filename, 30);

        printf("%s\n", inner_filename);
        files_count++;

        int res = read_file(inner_filename);
        if (res != -1) {
            files_count += res;
        }
    }
    fclose(f);

    return files_count;
}