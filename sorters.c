#include <stdio.h>
#include <string.h>
#include "person.h"

void sort_persons(struct person_t* persons, int size, int (*compare_fun)(struct person_t* person1, struct person_t* person2)) {
    struct person_t tmp;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (compare_fun(persons+i, persons+j) > 0) {
                tmp = *(persons+i);
                *(persons+i) = *(persons+j);
                *(persons+j) = tmp;
            }
        }
    }
}

int compare_by_name(struct person_t* person1, struct person_t* person2) {
    return strcmp(person1->name, person2->name);
}
int compare_by_age(struct person_t* person1, struct person_t* person2) {
    return person1->age - person2->age;
}

int (*get_comparator(int type))(struct person_t* person1, struct person_t* person2) {
    int (*comparators[2])(struct person_t* person1, struct person_t* person2) = {compare_by_name, compare_by_age};

    if (type != 0 && type != 1) {
        return NULL;
    }

    return comparators[type];
}