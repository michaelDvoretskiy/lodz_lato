#ifndef CODE_CALCULATOR_H
#define CODE_CALCULATOR_H
struct calculator_t {
    void* (*add)(const void*, const void*);
    void* (*sub)(const void*, const void*);
};

struct input_output_t {
    int (*read_input)(void**, void**);
    void (*show_result)(void*);
};

struct calculator_t* create_calculator(int calculator_type);
struct input_output_t* create_input_output(int type);
#endif //CODE_CALCULATOR_H
