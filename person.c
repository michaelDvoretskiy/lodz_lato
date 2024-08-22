#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

struct person_t* create_persons() {
    struct person_t* persons = malloc(sizeof(struct person_t) * 5);

    for (int i = 0; i < 5; i++) {
        (persons+i)->name = malloc(sizeof(char) * 20);
    }

    strcpy(persons->name, "Father");
    persons->age = 44;

    strcpy((persons+1)->name, "Mather");
    (persons+1)->age = 44;

    strcpy((persons+2)->name, "Mariia");
    (persons+2)->age = 19;

    strcpy((persons+3)->name, "Ivan");
    (persons+3)->age = 14;

    strcpy((persons+4)->name, "Anna");
    (persons+4)->age = 8;

    return persons;
}

void destroy_persons(struct person_t* persons, int size) {
    for (int i = 0; i < size; i++) {
        free((persons+i)->name);
    }
    free(persons);
}

void display_persons(struct person_t* persons, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s, %d\n", (persons+i)->name, (persons+i)->age);
    }
    printf("================\n");
}