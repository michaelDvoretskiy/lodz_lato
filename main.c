#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

struct message_t {
    char a;
    double b;
    int c;
};

int field_number(int byte_number) {
    if (byte_number >= offsetof(struct message_t, a) && byte_number < offsetof(struct message_t, a) + sizeof(char)) {
        return 1;
    }
    if (byte_number >= offsetof(struct message_t, b) && byte_number < offsetof(struct message_t, b) + sizeof(double)) {
        return 2;
    }
    if (byte_number >= offsetof(struct message_t, c) && byte_number < offsetof(struct message_t, c) + sizeof(int)) {
        return 3;
    }
    return 0;
}

struct message_t* read_file(char* filename, int* size) {
    if (filename == NULL){
        return NULL;
    }

    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        return NULL;
    }

    // первый unsigned int в файле - это количество байт данных в файле (считая после этих данных)
    int bytes_to_read_from_file;
    int read_res = fread(&bytes_to_read_from_file, sizeof(unsigned int), 1, f);
    if (read_res != 1) {
        fclose(f);
        printf("file is corrupted\n");
        return NULL;
    }

    // если количество байт не делется нацело на размер структуры, то фигня
    if (bytes_to_read_from_file % sizeof(struct message_t) != 0) {
        fclose(f);
        printf("file is corrupted\n");
        return NULL;
    }

    // считаем количествво сообщений в файле
    int number_of_messages = bytes_to_read_from_file / sizeof(struct message_t);
    if (number_of_messages == 0) {
        fclose(f);
        printf("file is corrupted\n");
        return NULL;
    }

    struct message_t* m = malloc(number_of_messages * sizeof(struct message_t));
    if (m == NULL) {
        fclose(f);
        printf("Failed to allocate memory\n");
        return NULL;
    }

    read_res = fread(m, sizeof(struct message_t), number_of_messages, f);
    if (read_res != number_of_messages) {
        fclose(f);
        free(m);
        printf("file is corrupted\n");
        return NULL;
    }

    *size = number_of_messages;

    return m;
}

char* read_message(struct message_t* m, int size) {
    if (m == NULL || size <= 0) {
        return NULL;
    }

    int bytes_quantity = sizeof(struct message_t);

    char* message_text = malloc(size*11+1);
    int message_cur_symbol_number = 0;
    if (message_text == NULL) {
        printf("Failed to allocate memory\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        char* chr = (char *) (m + i);
        for (int j = 0; j < bytes_quantity; j++) {
            if (field_number(j) == 0) {
                *(message_text+message_cur_symbol_number) = *(chr+j);
                message_cur_symbol_number++;
            }
        }
    }
    *(message_text+message_cur_symbol_number) = '\0';

    return message_text;
}

int main() {
    char*  filename = "messages";
    int number_of_messages = 0;
    struct message_t* m = read_file(filename, &number_of_messages);
    if (m != NULL) {
        char* message_text = read_message(m, number_of_messages);
        if (message_text != NULL) {
            printf("%s\n", message_text);
            free(message_text);
        }
        free(m);
    }

    return 0;
}
