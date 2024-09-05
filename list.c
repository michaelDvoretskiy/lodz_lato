#include <stdlib.h>
#include <ctype.h>
#include "list.h"

int read_header(struct header_t* head, FILE* fp) {
    if (fp == NULL) {
        return 1;
    }

    rewind(fp);

    char buf[1024];

    int header_words_count = 0;
    while (header_words_count == 0 && !feof(fp)) {
        int status = read_line(fp, buf);
        if (status != 0) {
            printf("cannot read the header\n");
            return 4;
        }
        header_words_count = count_words(buf);
    }
    if (header_words_count == 0) {
        printf("cannot read the header\n");
        return 4;
    }

    head->size = header_words_count;
    head->types = NULL;
    head->names = NULL;

    head->names = malloc(head->size * sizeof(char*));
    if (head->names == NULL) {
        printf("failed to allocate memory\n");
        free_header(head);
        return 2;
    }
    for (int i = 0; i < header_words_count; i++) {
        *(head->names + i) = NULL;
    }
    for (int i = 0; i < header_words_count; i++) {
        char* word = get_word(buf, i);
        if (word == NULL) {
            printf("failed to allocate memory\n");
            free_header(head);
            return 2;
        }
        *(head->names + i) = word;
    }

    int line_words_count = 0;
    while (line_words_count == 0 && !feof(fp)) {
        int status = read_line(fp, buf);
        if (status != 0) {
            printf("cannot read the first line\n");
            free_header(head);
            return 4;
        }
        line_words_count = count_words(buf);
    }
    if (line_words_count == 0) {
        printf("cannot read the first line\n");
        free_header(head);
        return 4;
    }

    if (header_words_count != line_words_count) {
        printf("smth wrong with columns\n");
        free_header(head);
        return 4;
    }

    head->types = malloc(head->size * sizeof(enum type_t));
    if (head->types == NULL) {
        printf("failed to allocate memory\n");
        free_header(head);
        return 2;
    }
    for (int i = 0; i < line_words_count; i++) {
        char* word = get_word(buf, i);
        if (word == NULL) {
            printf("failed to allocate memory\n");
            free_header(head);
            return 2;
        }
        *(head->types + i) = get_type(word);
        free(word);
    }

    return 0;
}

int read_file(struct list_t** list, const char* fname) {
    return 0;
}

void free_header(struct header_t* hd) {
    if (hd == NULL) {
        return;
    }
    if (hd->types != NULL) {
        free(hd->types);
    }
    for (int i = 0; i < hd->size; i++) {
        if (*(hd->names + i) != NULL) {
            free(*(hd->names + i));
        }
    }
    if (hd->names != NULL) {
        free(hd->names);
    }

    free(hd);
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
    *(line + i) = '\0';

    return 0;
}

int is_white_space(char chr) {
    if (chr == ' ' || chr == '\t' || chr == '\0' || chr == '\r' || chr == '\n' || chr == EOF) {
        return 1;
    }
    return 0;
}

int count_words(char* line) {
    int res = 0;
    int i = 0;
    char prev_chr = ' ';
    while (*(line + i) != '\0') {
        char current_chr = *(line + i);
        if (is_white_space(current_chr) == 0 && is_white_space(prev_chr) == 1) {
            res++;
        }
        prev_chr = *(line + i);
        i++;
    }

    return res;
}

char* get_word(char* line, int num) {
    int cur_word = 0;
    int i = 0;
    char prev_chr = ' ';
    int found = 0;

    while (*(line + i) != '\0') {
        char current_chr = *(line + i);
        if (is_white_space(current_chr) == 0 && is_white_space(prev_chr) == 1) {
            cur_word++;
        }
        if (cur_word == num + 1) {
            found = 1;
            break;
        }
        prev_chr = *(line + i);
        i++;
    }

    if (found == 0) {
        return NULL;
    }

    int word_begin = i;
    int word_end = i;
    while (*(line + word_end) != '\0' && is_white_space(*(line + word_end)) == 0) {
        word_end++;
    }
//    printf("%d %d\n", word_begin, word_end);

    char* res = malloc(word_end - word_begin + 1);
    if (res == NULL) {
        return NULL;
    }
    for (int i = word_begin; i < word_end; i++) {
        *(res + i - word_begin) = *(line + i);
    }
    *(res + word_end - word_begin) = '\0';

    return res;
}

int is_int(char* word) {
    int res = 1;
    int i = 0;
    while (*(word + i) != '\0') {
        int is_ok = 0;
        if (isdigit(*(word + i))) {
            is_ok = 1;
        } else if(i == 0 && *(word + i) == '-') {
            is_ok = 1;
        }
        if (is_ok == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}

int is_dbl(char* word) {
    int res = 1;
    int i = 0;
    int points_count = 0;
    while (*(word + i) != '\0') {
        int is_ok = 0;
        if (isdigit(*(word + i))) {
            is_ok = 1;
        } else if(i == 0 && *(word + i) == '-') {
            is_ok = 1;
        } else if(*(word + i) == '.') {
            is_ok = 1;
            points_count++;
            if (points_count > 1) {
                return 0;
            }
        }
        if (is_ok == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}

enum type_t get_type(char* word) {
    if (is_int(word) == 1) {
        return INT;
    }
    if (is_dbl(word) == 1) {
        return DBL;
    }
    return STR;
}

void show_header(struct header_t* header) {
    if (header == NULL) {
        return;
    }
    for (int i = 0; i < header->size; i++) {
        printf("%s ", *(header->names + i));
        if (*(header->types + i) == INT) {
            printf("integer\n");
        } else if (*(header->types + i) == DBL) {
            printf("double\n");
        } else if (*(header->types + i) == STR) {
            printf("string\n");
        }
    }
}