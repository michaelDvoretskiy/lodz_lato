#include <stdlib.h>
#include <ctype.h>
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