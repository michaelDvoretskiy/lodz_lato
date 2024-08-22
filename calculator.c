#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"
#include "operations_int.h"
#include "operations_float.h"
#include "operations_point.h"

struct calculator_t* create_calculator(int calculator_type) {
    void* (*add_array[3])(const void*, const void*) = {add_int, add_float, add_point};
    void* (*sub_array[3])(const void*, const void*) = {sub_int, sub_float, sub_point};

    struct calculator_t* calc = malloc(sizeof(struct calculator_t));
    if (calc == NULL) {
        return NULL;
    }

    calc->add = add_array[calculator_type];
    calc->sub = sub_array[calculator_type];

    return calc;
}

struct input_output_t* create_input_output(int type) {
    int (*read_input_array[3])(void**, void**) = {read_input_int, read_input_float, read_input_point};
    void (*show_result_array[3])(void*) = {show_result_int, show_result_float, show_result_point};

    struct input_output_t* io = malloc(sizeof(struct input_output_t));
    if (io == NULL) {
        return NULL;
    }

    io->read_input = read_input_array[type];
    io->show_result = show_result_array[type];

    return io;
}