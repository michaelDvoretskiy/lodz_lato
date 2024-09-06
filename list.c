#include <stdlib.h>
#include <ctype.h>
#include "list.h"

int read_header(struct header_t* head, FILE* fp) {
    if (fp == NULL && head == NULL) {
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
    if (head->names == NULL) {
        printf("failed to allocate memory\n");
        free_header(head);
        return 2;
    }
    for (unsigned int i = 0; i < header_words_count; i++) {
        *(head->names + i) = NULL;
    }
    for (unsigned int i = 0; i < header_words_count; i++) {
        char* word = get_word(buf, (int) i);
        if (word == NULL) {
            printf("failed to allocate memory\n");
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
    if (head->types == NULL) {
        printf("failed to allocate memory\n");
        free_header(head);
        return 2;
    }
    for (unsigned int i = 0; i < line_words_count; i++) {
        char* word = get_word(buf, (int)i);
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
    if (fname == NULL) {
        return 1;
    }

    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("cannot open file\n");
        return 3;
    }

    struct header_t* header = malloc(sizeof(struct header_t));
    if (header == NULL) {
        printf("failed to allocate memory\n");
        return 2;
    }
    int read_header_status = read_header(header, fp);
    if (read_header_status != 0) {
        free_header(header);
        return read_header_status;
    }

    rewind(fp);

    char buf[1024];
    int rows_count = 0;
    while (!feof(fp)) {
        int status = read_line(fp, buf);
        if (status != 0) {
            printf("cannot read the line\n");
            return 4;
        }
        int row_words_count = count_words(buf);
        if (row_words_count != 0) {
            rows_count++;
        }
    }

    *list = malloc(rows_count * sizeof(struct list_t));
    if (*list == NULL) {
        free_header(header);
        printf("failed to allocate memory\n");
        return 2;
    }

    for (int i = 0; i < rows_count-1; i++) {
        (*list+i)->header = header;
        (*list+i)->head = NULL;
        (*list+i)->tail = NULL;
    }
    (*list+rows_count-1)->header = NULL;
    (*list+rows_count-1)->head = NULL;
    (*list+rows_count-1)->tail = NULL;

    rewind(fp);

    int current_line_number = 0;
    while (!feof(fp)) {
        int status = read_line(fp, buf);
        if (status != 0) {
            printf("cannot read the line\n");
            free_list(list);
            free_header(header);
            return 4;
        }
        unsigned int line_words_count = count_words(buf);
        if (line_words_count > 0) {
            if (current_line_number > 0) {
                if (header->size != line_words_count) {
                    printf("smth wrong with columns\n");
                    free_list(list);
                    free_header(header);
                    return 4;
                }

                struct list_t* current_list = (*list + current_line_number - 1);

                for (unsigned int i = 0; i < header->size; i++) {
                    char* word = get_word(buf, (int)i);
                    if (word == NULL) {
                        printf("failed to allocate memory\n");
                        free_list(list);
                        free_header(header);
                        return 2;
                    }
                    struct node_t* new_node = malloc(sizeof(struct node_t));
                    if (new_node == NULL) {
                        free_list(list);
                        free_header(header);
                        return 2;
                    }
                    new_node->vals = malloc(sizeof(union val_t));
                    if (new_node->vals == NULL) {
                        free(new_node);
                        free_list(list);
                        free_header(header);
                        return 2;
                    }

                    new_node->prev = current_list->tail;
                    new_node->next = NULL;

                    if (current_list->tail != NULL) {
                        current_list->tail->next = new_node;
                    }
                    current_list->tail = new_node;

                    if (current_list->head == NULL) {
                        current_list->head = new_node;
                    }
//                    printf("Node %d %d %d\n", new_node, new_node->prev, new_node->next);
//                    printf("list %d %d %d\n", current_list, current_list->head, current_list->tail);
//                    printf("Prev node %d %d %d\n", new_node->prev, new_node->prev == NULL ? 0 : new_node->prev->prev, new_node->prev == NULL ? 0 : new_node->prev->next);

                    if (*(header->types + i) == INT) {
                        new_node->vals->as_int = atoi(word);
                        free(word);
                    } else if (*(header->types + i) == DBL) {
                        double val;
                        sscanf(word, "%lf", &val);
                        new_node->vals->as_double = val;
                        free(word);
                    } else {
                        new_node->vals->as_str = word;
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
    }
    for (unsigned int i = 0; i < hd->size; i++) {
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
    if (*list == NULL) {
        return;
    }
    int i = 0;
    while ((*list+i)->header != NULL) {
        struct node_t* cur_node = (*list+i)->head;
        int cur_node_number = 0;
        while (cur_node != NULL) {
            enum type_t cur_node_type = *((*list+i)->header->types + cur_node_number);
            if (cur_node_type == STR) {
                free(cur_node->vals->as_str);
            }
            struct node_t* next_node = cur_node->next;
            free(cur_node);
            cur_node = next_node;
            cur_node_number++;
        }
        i++;
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
    int i = 0;
    while ((list+i)->header != NULL) {
        struct node_t* cur_node = (list+i)->head;
        int cur_node_number = 0;
        while (cur_node != NULL) {
            enum type_t cur_node_type = *((list+i)->header->types + cur_node_number);
            printf("%s:", *((list+i)->header->names + cur_node_number));
            if (cur_node_type == STR) {
                printf("%s ", cur_node->vals->as_str);
            }
            if (cur_node_type == INT) {
                printf("%d ", cur_node->vals->as_int);
            }
            if (cur_node_type == DBL) {
                printf("%lf ", cur_node->vals->as_double);
            }
            cur_node = cur_node->next;
            cur_node_number++;
        }
        printf("\n");
        i++;
    }
}