#include <stdlib.h>
#include <ctype.h>
#include "list.h"

#define DEBUG 0

int read_header(struct header_t* head, FILE* fp) {
    if (fp == NULL || head == NULL) {
        return 1;
    }

    rewind(fp);

    char buf[1024];

    unsigned int header_words_count = 0;
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

//    printf("header words count%d\n", header_words_count);
    head->size = header_words_count;
    head->types = NULL;
    head->names = NULL;

    head->names = malloc(head->size * sizeof(char*));
    if (DEBUG == 1) printf("allocated %lu for the names*\n", head->size * sizeof(char*));
    if (head->names == NULL) {
        printf("failed to allocate memory 1\n");
        free_header(head);
        return 2;
    }
    for (unsigned int i = 0; i < header_words_count; i++) {
        *(head->names + i) = NULL;
    }
    for (unsigned int i = 0; i < header_words_count; i++) {
        char* word = get_word(buf, (int) i);
        if (word == NULL) {
            printf("failed to allocate memory 2\n");
            free_header(head);
            return 2;
        }
        *(head->names + i) = word;
    }

    unsigned int line_words_count = 0;
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
    if (DEBUG == 1) printf("allocated %lu for the types*\n", head->size * sizeof(enum type_t));
    if (head->types == NULL) {
        printf("failed to allocate memory 3\n");
        free_header(head);
        return 2;
    }
    for (unsigned int i = 0; i < line_words_count; i++) {
        int word_start;
        int word_stop = 0;
        get_word_v2(buf, (int)i, &word_start, &word_stop);
        *(head->types + i) = get_type_v2(buf, word_start, word_stop);
    }

    return 0;
}

int read_file(struct list_t** list, const char* fname) {
    if (list == NULL || fname == NULL) {
        return 1;
    }

    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("cannot open file\n");
        return 3;
    }

    *list = malloc(sizeof(struct list_t));
    if (DEBUG == 1) printf("allocated %lu for the list\n", sizeof(struct list_t));
    if (*list == NULL) {
        printf("failed to allocate memory 4\n");
        fclose(fp);
        return 2;
    }
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->header = NULL;

    (*list)->header = malloc(sizeof(struct header_t));
    if (DEBUG == 1) printf("allocated %lu for the header\n", sizeof(struct header_t));
    if ((*list)->header == NULL) {
        free_list(list);
        printf("failed to allocate memory 5\n");
        fclose(fp);
        return 2;
    }
    int read_header_status = read_header((*list)->header, fp);
    if (read_header_status != 0) {
        free_list(list);
        fclose(fp);
        return read_header_status;
    }

    rewind(fp);

    char buf[1024];

    int current_line_number = 0;
    while (!feof(fp)) {
        int status = read_line(fp, buf);
        if (status != 0) {
            printf("cannot read the line\n");
            free_list(list);
            fclose(fp);
            return 4;
        }

        unsigned int line_words_count = count_words(buf);
        if (line_words_count > 0) {
            if (current_line_number > 0) {
                if ((*list)->header->size != line_words_count) {
                    printf("smth wrong with columns\n");
                    free_list(list);
                    fclose(fp);
                    return 4;
                }

                struct node_t* new_row = malloc(sizeof(struct node_t));
                if (new_row == NULL) {
                    free_list(list);
                    printf("failed to allocate memory 6\n");
                    fclose(fp);
                    return 2;
                }

                new_row->prev = (*list)->tail;
                new_row->next = NULL;

                if ((*list)->tail != NULL) {
                    (*list)->tail->next = new_row;
                }
                (*list)->tail = new_row;

                if ((*list)->head == NULL) {
                    (*list)->head = new_row;
                }

                new_row->vals = malloc(sizeof(union val_t) * (*list)->header->size);
                if (DEBUG == 1) printf("allocated %lu for the node vals\n", sizeof(union val_t) * (*list)->header->size);
                if (new_row->vals == NULL) {
                    free_list(list);
                    printf("failed to allocate memory 7\n");
                    fclose(fp);
                    return 2;
                }

                for (unsigned int i = 0; i < (*list)->header->size; i++) {
                    (new_row->vals + i)->as_str = NULL;
                }

                for (unsigned int i = 0; i < (*list)->header->size; i++) {
                    char* word = get_word(buf, (int)i);
                    if (word == NULL) {
                        printf("failed to allocate memory 8\n");
                        free_list(list);
                        fclose(fp);
                        return 2;
                    }

                    if (*((*list)->header->types + i) == INT) {
                        (new_row->vals+i)->as_int = atoi(word);
                        free(word);
                    } else if (*((*list)->header->types + i) == DBL) {
                        double val;
                        sscanf(word, "%lf", &val);
                        (new_row->vals+i)->as_double = val;
                        free(word);
                    } else {
                        (new_row->vals+i)->as_str = word;
                    }
                }
            }
            current_line_number++;
        }
    }
    fclose(fp);

    return 0;
}

void free_header(struct header_t* hd) {
    if (hd == NULL) {
        return;
    }
    if (hd->types != NULL) {
        free(hd->types);
        hd->types = NULL;
    }
    if (hd->names != NULL) {
        for (unsigned int i = 0; i < hd->size; i++) {
            if (*(hd->names + i) != NULL) {
                free(*(hd->names + i));
            }
        }
        free(hd->names);
        hd->names = NULL;
    }

//    free(hd);
}

void free_list(struct list_t** list) {
    if (*list == NULL) {
        return;
    }
    struct node_t* cur_row = (*list)->head;
    while (cur_row != NULL) {
        if (cur_row->vals != NULL) {
            for (unsigned int i = 0; i < (*list)->header->size; i++) {
                enum type_t cur_val_type = *((*list)->header->types + i);
                if (cur_val_type == STR && (cur_row->vals + i)->as_str != NULL) {
                    free((cur_row->vals + i)->as_str);
                }
            }
            free(cur_row->vals);
        }
        struct node_t* next_row = cur_row->next;
        free(cur_row);
        cur_row = next_row;
    }

    if ((*list)->header != NULL) {
        free_header((*list)->header);
        free((*list)->header);
    }

    free(*list);
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

    char* res = malloc((word_end - word_begin + 1) * sizeof(char));
    if (DEBUG == 1) printf("allocated %ld for the word\n", (word_end - word_begin + 1) * sizeof(char));
    if (res == NULL) {
        return NULL;
    }
    for (int j = word_begin; j < word_end; j++) {
        *(res + j - word_begin) = *(line + j);
    }
    *(res + word_end - word_begin) = '\0';

    return res;
}

int is_int(char* word) {
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

void get_word_v2(char* line, int num, int* start, int* stop) {
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
        return;
    }

    int word_begin = i;
    int word_end = i;
    while (*(line + word_end) != '\0' && is_white_space(*(line + word_end)) == 0) {
        word_end++;
    }

    *start = word_begin;
    *stop = word_end;
}

int is_int_v2(char* line, int start, int stop) {
    for (int i = start; i < stop; i++) {
        int is_ok = 0;
        if (isdigit(*(line + i))) {
            is_ok = 1;
        } else if(i == start && *(line + i) == '-') {
            is_ok = 1;
        }
        if (is_ok == 0) {
            return 0;
        }
    }
    return 1;
}

int is_dbl_v2(char* line, int start, int stop) {
    int points_count = 0;
    for (int i = start; i < stop; i++) {
        int is_ok = 0;
        if (isdigit(*(line + i))) {
            is_ok = 1;
        } else if(i == start && *(line + i) == '-') {
            is_ok = 1;
        } else if(*(line + i) == '.') {
            is_ok = 1;
            points_count++;
            if (points_count > 1) {
                return 0;
            }
        }
        if (is_ok == 0) {
            return 0;
        }
    }
    return 1;
}

enum type_t get_type_v2(char* line, int start, int stop) {
    if (is_int_v2(line, start, stop) == 1) {
        return INT;
    }
    if (is_dbl_v2(line, start, stop) == 1) {
        return DBL;
    }
    return STR;
}

void show_header(struct header_t* header) {
    if (header == NULL) {
        return;
    }
    for (unsigned int i = 0; i < header->size; i++) {
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

void show_list(struct list_t* list) {
    if (list == NULL) {
        return;
    }
    struct node_t* cur_row = list->head;
    while (cur_row != NULL) {
        if (cur_row->vals != NULL) {
            for (unsigned int i = 0; i < list->header->size; i++) {
                enum type_t cur_val_type = *(list->header->types + i);
                printf("%s:", *(list->header->names + i));
                if (cur_val_type == STR) {
                    printf("%s ", (cur_row->vals + i)->as_str);
                }
                if (cur_val_type == INT) {
                    printf("%d ", (cur_row->vals + i)->as_int);
                }
                if (cur_val_type == DBL) {
                    printf("%lf ", (cur_row->vals + i)->as_double);
                }
            }
            printf("\n");
        }
        cur_row = cur_row->next;
    }
}