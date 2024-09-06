#ifndef CODE_LIST_H
#define CODE_LIST_H

#include <stdio.h>

enum type_t {
    INT,
    DBL,
    STR
};

struct list_t {
    struct node_t* head;
    struct node_t* tail;
    struct header_t* header;
};

struct header_t {
    unsigned int size;
    enum type_t* types;
    char** names;
};

struct node_t {
    union val_t* vals;
    struct node_t* prev;
    struct node_t* next;
};

union val_t {
    int as_int;
    double as_double;
    char* as_str;
};

int read_header(struct header_t* head, FILE* fp);
int read_file(struct list_t** list, const char* fname);

void free_header(struct header_t* hd);
void free_list(struct list_t** list);

int read_line(FILE* fp, char* line);
int is_white_space(char chr);
int count_words(char* line);
char* get_word(char* line, int num);

int is_int(char* word);
int is_dbl(char* word);
enum type_t get_type(char* word);

void show_header(struct header_t* header);
void show_list(struct list_t* list);

#endif //CODE_LIST_H
