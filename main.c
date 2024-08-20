#include <stdio.h>
#include <stdlib.h>

// тут нет валидации для предложения, считается, что слова разделены одним пробелом,
// и ни в начеле ни в конце предложения нет пробела
// знаки припинания будут частью слова

char* read_string(int start_len, int step) {
    int cur_str_len = start_len;
    char* str = malloc(sizeof(char) * (cur_str_len + 1));
    if (str == NULL) {
        printf("Input error");
        return NULL;
    }

    printf("Enter string:\n");
    char chr;
    if (scanf("%c", &chr) != 1) {
        printf("Input error");
        return NULL;
    }
    int i = 0;
    while (chr != '\n') {
        if (i >= cur_str_len) {
            cur_str_len += step;
            char* new_str = realloc(str, sizeof(char) * (cur_str_len + 1));
            if (new_str == NULL) {
                printf("Input error");
                return NULL;
            }
            str = new_str;
        }
        *(str + i) = chr;
        i++;
        if (scanf("%c", &chr) != 1) {
            printf("Input error");
            return NULL;
        }
    }
    *(str + i) = '\0';

    return str;
}

void destroy_sentence(char** words) {
    if (words == NULL) {
        return;
    }
    int i = 0;
    while (*(words + i) != NULL) {
        free(*(words + i));
        i++;
    }
    free(words);
}

int create_sentence(char*** words, char* input) {

    if (*words == NULL || input == NULL) {
        return 1;
    }

    // считаем количество слов
    int words_count = 0;
    int i = 0;
    while (*(input + i) != '\0') {
        if (*(input + i) == ' ') {
            words_count++;
        }
        i++;
    }

    if (i > 0) {
        // слов на 1 больше, чем пробелов и еще один последнний елемент,
        // чтобы записать туда NULL - признак конца предложенния
        words_count += 2;
    }

    if (words_count == 0) {
        return 2;
    }

    *words = malloc(sizeof(char*) * words_count);
    printf("allocated memory for %d words\n", words_count);
    if (*words == NULL) {
        return 3;
    }
    for (int j = 0; j < words_count; j++) {
        *(*words + j) = NULL;
    }

    // считаем количество букв в каждом слове
    int current_word = 0;
    int symbols_in_word = 0;
    i = 0;
    while (*(input + i) != '\0') {
        if (*(input + i) == ' ') {
            *(*words + current_word) = malloc(sizeof(char) * (symbols_in_word + 1));
            printf("allocated memory for %d symbols in word %d\n", symbols_in_word + 1, current_word + 1);
            if (*words == NULL) {
                destroy_sentence(*words);
                return 3;
            }

            current_word++;
            symbols_in_word = 0;
        } else {
            symbols_in_word++;
        }
        i++;
    }

    // выделяем память под последнее слово
    *(*words + current_word) = malloc(sizeof(char) * symbols_in_word);
    printf("allocated memory for %d symbols in word %d\n", symbols_in_word + 1, current_word + 1);
    if (*words == NULL) {
        destroy_sentence(*words);
        return 3;
    }

    // теперь читаем данные из input и записываем в words
    current_word = 0;
    int current_symbol = 0;
    i = 0;
    while (*(input + i) != '\0') {
        if (*(input + i) == ' ') {
            *(*(*words + current_word) + current_symbol) = '\0';
            current_word++;
            current_symbol = 0;
        } else {
            *(*(*words + current_word) + current_symbol) = *(input + i);
            current_symbol++;
        }
        i++;
    }
    // конец строки для последнего слова последнего предложения
    *(*(*words + current_word) + current_symbol) = '\0';

    return 0;
}

void display_sentence(char** words) {
    if (words == NULL) {
        return;
    }
    printf("============\n");
    int i = 0;
    while (*(words + i) != NULL) {
        printf("%s\n", *(words + i));
        i++;
    }
    printf("============\n");
}

int main() {
    char* text = read_string(100, 50);
    char** sentence;
    if (create_sentence(&sentence, text) != 0) {
        return 1;
    }
    display_sentence(sentence);
    destroy_sentence(sentence);

    return 0;
}
