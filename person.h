#ifndef CODE_PERSON_H
#define CODE_PERSON_H

struct person_t {
    char* name;
    int age;
};

struct person_t* create_persons();
void destroy_persons(struct person_t* persons, int size);
void display_persons(struct person_t* persons, int size);

int compare_by_name(struct person_t* person1, struct person_t* person2);
int compare_by_age(struct person_t* person1, struct person_t* person2);

void sort_persons(struct person_t* persons, int size, int (*compare_fun)(struct person_t* person1, struct person_t* person2));

int (*get_comparator(int type))(struct person_t* person1, struct person_t* person2);

#endif //CODE_PERSON_H
