#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int main() {
    struct student_t s;
    s.name = malloc(20);
    strcpy(s.name, "Vasya");
    s.number = 123;

    printf("Student: %s, number %d", s.name, s.number);
    return 0;
}
