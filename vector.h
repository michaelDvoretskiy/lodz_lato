#ifndef CODE_VECTOR_H
#define CODE_VECTOR_H

struct my_vector_t {
    int* data;
    int size;
    int capacity;
};

struct my_vector_t* create(int capacity);

int increase_size(struct my_vector_t* v);

int decrease_size(struct my_vector_t* v);

void show(struct my_vector_t* v);

void destroy(struct my_vector_t* v);

int add(struct my_vector_t* v, int value);

int rem_by_index(struct my_vector_t* v, int index);

int rem_all_by_value(struct my_vector_t* v, int value);

int get(struct my_vector_t* v, int index, int* value);

int set(struct my_vector_t* v, int index, int value);

#endif //CODE_VECTOR_H
