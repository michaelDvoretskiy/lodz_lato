#ifndef CODE_MY_STRINGS_H
#define CODE_MY_STRINGS_H

#define ONE_TEXT_SIZE 100

int read_number_of_texts(int* number_of_texts);

int create_texts(char*** texts, int number_of_texts);

int read_texts(char** texts, int number_of_texts);

void display_texts(char** texts, int number_of_texts);

void destroy_texts(char** texts, int number_of_texts);

int concat_texts(char** text_result, int number_of_texts, ...);

#endif //CODE_MY_STRINGS_H
