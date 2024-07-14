#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student_t {
    char name[31];
    char surname[21];
    int number;
};

void show(struct student_t* s) {
    printf("%s %s, %d\n", s->name, s->surname, s->number);
}

// функція читає шаблон з трьох підрядків, так простіше,
// але він більш обмежений у можливостях знайти всі можливі
// помилки вводу
struct student_t* read1(struct student_t* student, int* err) {
    *err = 0;

    char input1[31];
    char input2[21];
    char input3[11];

    printf("Enter a string:");
    int res = scanf("%30[^,],%20[^,],%10s", input1, input2, input3);

    if (res != 3) {
        printf("incorrect input");
        *err = 1;
        return NULL;
    }

    // можемо видалити проміжки, використавши функцію string_trim, реалізовану у 2-1-4
    // input1 = string_trim(input1);
    // input2 = string_trim(input2);
    // input3 = string_trim(input3);

    // модемо перевірити, чи у третьому параметрі тільки цифри,
    // використивши функцію isNumber з 3-1-1
    // if (isNumber(input3) != 1) {
    //      printf("incorrect input");
    //      *err = 2;
    //      return NULL;
    // }

    strcpy(student->name, input1);
    strcpy(student->surname, input2);
    student->number = atoi(input3);

    return student;
}

// читаємо символи один за одним, довше, але дає змогу
// втрутитись у прочец читання
struct student_t* read2(struct student_t* student, int* err) {
    *err = 0;

    char* word = malloc(40);
    // or it can be
    // char word[40];
    int word_current_character = 0;
    int current_word = 0;

    printf("Enter a string:");
    char ch;
    scanf("%c", &ch);
    while (1) {
        if (ch == ',' || ch == '\n') {
            *(word + word_current_character) = '\0';
            // можемо видалити проміжки, використавши функцію string_trim, реалізовану у 2-1-4
            // word = string_trim(word);
            if (current_word == 0) {
                strcpy(student->name, word);
            } else if (current_word == 1) {
                strcpy(student->surname, word);
            } else {
                // модемо перевірити, чи у третьому параметрі тільки цифри,
                // використивши функцію isNumber з 3-1-1
                // if (isNumber(word) != 1) {
                //      printf("incorrect input");
                //      *err = 2;
                //      return NULL;
                // }
                student->number = atoi(word);
            }

            word_current_character = 0;
            current_word++;
        } else {
            *(word + word_current_character) = ch;
            word_current_character++;
        }
        if (ch == '\n') {
            break;
        }
        scanf("%c", &ch);
    }

    if (current_word != 3) {
        printf("incorrect input");
        *err = 3;
        return NULL;
    }

    return student;
}

void read_eol() {
    char ch;
    scanf("%c", &ch);
    while (ch != '\n') {
        scanf("%c", &ch);
    }
}

int main() {
    int err;
    struct student_t s;
    struct student_t* s_res;
    s_res = read1(&s, &err);
    if (err == 0) {
        show(s_res);
    }
    read_eol();

    s_res = read2(&s, &err);
    if (err == 0) {
        show(s_res);
    }

    return 0;
}
