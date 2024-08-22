#ifndef CODE_PERSON_H
#define CODE_PERSON_H

struct person_t {
    char* name;
    int age;
};

struct person_t* create_persons();
void destroy_persons(struct person_t* persons, int size);
void display_persons(struct person_t* persons, int size);

void sort_by_name(struct person_t* persons, int size);
void sort_by_age(struct person_t* persons, int size);

void (*get_sorter(int type))(struct person_t* persons, int size);

#endif //CODE_PERSON_H
