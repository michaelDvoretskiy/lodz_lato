#include <stdio.h>
#include <string.h>
#include "person.h"

void sort_by_name(struct person_t* persons, int size) {
    struct person_t tmp;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp((persons+i)->name, (persons+j)->name) > 0) {
                tmp = *(persons+i);
                *(persons+i) = *(persons+j);
                *(persons+j) = tmp;
            }
        }
    }
}

void sort_by_age(struct person_t* persons, int size) {
    struct person_t tmp;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if ((persons+i)->age > (persons+j)->age) {
                tmp = *(persons+i);
                *(persons+i) = *(persons+j);
                *(persons+j) = tmp;
            }
        }
    }
}

void (*get_sorter(int type))(struct person_t* persons, int size) {
    void (*sorters[2])(struct person_t* persons, int size) = {sort_by_name, sort_by_age};

    if (type != 0 && type != 1) {
        return NULL;
    }

    return sorters[type];
}