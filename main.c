#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person_t {
    char* first_name;
    char* last_name;
};

int extract_names(char* input, char** name1, char** name2)
{
    if (input == NULL) {
        return 1;
    }

    *name1 = input;
    int i = 0;
    while (*(input + i) != '\0') {
        if (*(input + i) == ' ') {
            *(input + i) = '\0';
            *name2 = input + i + 1;
        }
        i++;
    }

    return 0;
}

int main() {
    char* full_name = malloc(sizeof(char) * 15);
    strcpy(full_name, "John Smith");

    struct person_t* person = malloc(sizeof(struct person_t));
    if (extract_names(full_name, &(person->first_name), &(person->last_name)) != 0) {
        return 1;
    }

    printf("%s %s", person->first_name, person->last_name);

    return 0;
}
