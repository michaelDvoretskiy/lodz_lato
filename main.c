#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_t {
    char* first_name;
    char* last_name;
    int group_number;
};

int main() {
    struct student_t* students = malloc(sizeof(struct student_t) * 3);
    students->first_name = malloc(sizeof(char) * 10);
    strcpy(students->first_name, "Svitlana");
    students->last_name = malloc(sizeof(char) * 15);
    strcpy(students->last_name, "Dvoretska");
    students->group_number = 408;

    (students+1)->first_name = malloc(sizeof(char) * 10);
    strcpy((students+1)->first_name, "Mariia");
    (students+1)->last_name = malloc(sizeof(char) * 15);
    strcpy((students+1)->last_name, "Dvoretska");
    (students+1)->group_number = 208;

    (*(students+2)).first_name = malloc(sizeof(char) * 10);
    strcpy((*(students+2)).first_name, "Ivan");
    (*(students+2)).last_name = malloc(sizeof(char) * 15);
    strcpy((*(students+2)).last_name, "Dvoretskyi");
    (*(students+2)).group_number = 7;

    for (int i = 0; i < 3; i++) {
        printf("%s %s, group: %d\n", (students+i)->first_name, (students+i)->last_name, (students+i)->group_number);
        printf("==================\n");
    }

    for (int i = 0; i < 3; i++) {
        free((students+i)->first_name);
        free((students+i)->last_name);
    }
    free(students);

    return 0;
}
