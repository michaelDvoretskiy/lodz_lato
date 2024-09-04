#include "list.h"

int read_header(struct header_t* head, FILE* fp) {
    return 0;
}

int read_file(struct list_t** list, const char* fname) {
    return 0;
}

void free_header(struct header_t* hd) {

}

void free_list(struct list_t** list) {

}

int read_line(FILE* fp, char* line) {
    if (fp == NULL || line == NULL) {
        return 1;
    }

    int i = 0;
    char chr = fgetc(fp);
    while (chr != '\n' && !feof(fp)) {
        *(line + i) = chr;
        i++;
        chr = fgetc(fp);
    }

    return 0;
}