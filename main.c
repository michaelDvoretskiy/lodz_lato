#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_v1_t {
    char first_name[10];
    char last_name[15];
    int group_number;
};

struct student_v2_t {
    char* first_name;
    char* last_name;
    int group_number;
};

int main() {
    struct student_v1_t student1;
    strcpy(student1.first_name, "Ivan");
    strcpy(student1.last_name, "Dvoretskyi");
    student1.group_number = 7;
    printf("%s %s, group: %d\n", student1.first_name, student1.last_name, student1.group_number);
    printf("==================\n");

    struct student_v1_t* student2 = malloc(sizeof(struct student_v1_t));
    strcpy(student2->first_name, "Mariia");
    strcpy((*student2).last_name, "Dvoretska");
    student2->group_number = 209;
    printf("%s %s, group: %d\n", student2->first_name, student2->last_name, student2->group_number);
    printf("==================\n");

    struct student_v2_t student3;
    student3.first_name = malloc(sizeof(char) * 10);
    strcpy(student3.first_name, "Mikhailo");
    student3.last_name = malloc(sizeof(char) * 15);
    strcpy(student3.last_name, "Dvoretskyi");
    student3.group_number = 408;
    printf("%s %s, group: %d\n", student3.first_name, student3.last_name, student3.group_number);
    printf("==================\n");
    free(student3.first_name);
    free(student3.last_name);

    struct student_v2_t* student4 = malloc(sizeof(struct student_v2_t));
    student4->first_name = malloc(sizeof(char) * 10);
    strcpy(student4->first_name, "Svitlana");
    student4->last_name = malloc(sizeof(char) * 15);
    strcpy(student4->last_name, "Dvoretska");
    student4->group_number = 408;
    printf("%s %s, group: %d\n", student4->first_name, student4->last_name, student4->group_number);
    printf("==================\n");
    free(student4->first_name);
    free(student4->last_name);
    free(student4);

    return 0;
}
