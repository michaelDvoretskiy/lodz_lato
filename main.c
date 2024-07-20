#include <stdio.h>

int add_to_text_file(char* filename, char* data) {
    // a - відкриття для запису, створює файл, якщо нема, запис виконується в кінець файлу
    // a+ - можна накож і читати
    FILE* f = fopen(filename, "a+");
    if (f == NULL) {
        return 1;
    }
    int put_res = fputs(data, f);
    // gpt сказал, что вернется положительное ззначение, если ок, и -1 если не ок
    // хотя по факту мы таких проверок на успешность записи нигде в заданиях не делали
    if (put_res < 0) {
        fclose(f);
        return 1;
    }
    put_res = fputc('\n', f);
    if (put_res < 0) {
        fclose(f);
        return 1;
    }
    // можна і так ?
    put_res = fprintf(f, "%s\n", data);
    if (put_res < 0) {
        fclose(f);
        return 1;
    }

    fclose(f);
    return 0;
}

int main() {
    char file_name[31];
    printf("Enter name:\n");
    scanf("%30s", file_name);

    char str[10];
    for (int i = 0; i < 5; i++) {
        sprintf(str,"%s %d", "string", i);
        if (add_to_text_file(file_name, str) == 1) {
            printf("smth went wrong");
            return 1;
        }
    }

    return 0;
}
