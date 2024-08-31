#ifndef CODE_CALC_H
#define CODE_CALC_H

struct point_t {
    int x;
    int y;
};

int get_int_value(void* value, double* res);
int get_double_value(void* value, double* res);
int get_point_value(void* value, double* res);
int get_parameter_value(char type, void* value, double* res);

int make_add(double val1, double val2, double* res);
int make_sub(double val1, double val2, double* res);
int make_mult(double val1, double val2, double* res);
int make_div(double val1, double val2, double* res);
int make_operation(char operation, double val1, double val2, double* res);

int calculate(char* expression, double* res, ...);

#endif //CODE_CALC_H
