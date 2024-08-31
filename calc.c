#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#include "calc.h"

int get_int_value(void* value, double* res) {
    if (value == NULL || res == NULL) {
        return 1;
    }
    *res = *((int*) value);
    return 0;
}

int get_double_value(void* value, double* res) {
    if (value == NULL || res == NULL) {
        return 1;
    }
    *res = *((double*) value);
    return 0;
}

int get_point_value(void* value, double* res) {
    if (value == NULL || res == NULL) {
        return 1;
    }
    struct point_t* p = (struct point_t*) value;
    *res = sqrt(p->x * p->x + p->y * p->x);

    return 0;
}

int get_parameter_value(char type, void* value, double* res) {
    int (*value_getter[3]) (void*, double*) = {get_int_value, get_double_value, get_point_value};
    if (type == 'd') {
        return value_getter[0](value, res);
    }
    if (type == 'f') {
        return value_getter[1](value, res);
    }
    if (type == 'p') {
        return value_getter[2](value, res);
    }
    return 1;
}

int make_add(double val1, double val2, double* res) {
    if (res == NULL) {
        return 1;
    }
    *res = val1 + val2;
    return 0;
}

int make_sub(double val1, double val2, double* res) {
    if (res == NULL) {
        return 1;
    }
    *res = val1 - val2;
    return 0;
}

int make_mult(double val1, double val2, double* res) {
    if (res == NULL) {
        return 1;
    }
    *res = val1 * val2;
    return 0;
}

int make_div(double val1, double val2, double* res) {
    if (res == NULL) {
        return 1;
    }
    if (val2 == 0) {
        return 1;
    }
    *res = val1 / val2;
    return 0;
}

int make_operation(char operation, double val1, double val2, double* res) {
    if (res == NULL) {
        return 1;
    }
    int (*operation_maker[4]) (double, double, double*) = {make_add, make_sub, make_mult, make_div};
    if (operation == '+') {
        return operation_maker[0](val1, val2, res);
    }
    if (operation == '-') {
        return operation_maker[1](val1, val2, res);
    }
    if (operation == '*') {
        return operation_maker[2](val1, val2, res);
    }
    if (operation == '/') {
        return operation_maker[3](val1, val2, res);
    }
    return 1;
}


int calculate(char* expression, double* res, ...) {
    if (expression == NULL || res == NULL) {
        return 1;
    }

    *res = 0.0;
    // если 1, то следующее значение в шаблоне должно быть оператором, иначе типом данных
    int expected_operator = 0;
    // стартовое значение результата 0, первое прочитанное значение из выражения будем прибавлять к нулю
    char operator = '+';

    va_list args;
    va_start(args, res);

    while (*expression) {
        // пропускаем пробелы, если есть
        if (isspace(*expression)) {
            expression++;
            continue;
        }

        // если прочитали тип очередного параметра
        if (expected_operator == 0) {
            double param_value;
            int get_val_status;

            if (*expression == 'd') {
                int value = va_arg(args, int);
                get_val_status = get_parameter_value('d', &value, &param_value);
            } else if (*expression == 'f') {
                double value = va_arg(args, double);
                get_val_status = get_parameter_value('f', &value, &param_value);
            } else if (*expression == 'p') {
                struct point_t value = va_arg(args, struct point_t);
                get_val_status = get_parameter_value('p', &value, &param_value);
            } else {
                // какая то непонятная операция
                va_end(args);
                return 1;
            }

            if (get_val_status != 0) {
                va_end(args);
                return get_val_status;
            }

            int operation_status = make_operation(operator, *res, param_value, res);
            if (operation_status != 0) {
                va_end(args);
                return operation_status;
            }

            expected_operator = 1;
        } else {
            // если прочитали операцию
            operator = *expression;
            expected_operator = 0;
        }
        expression++;
        va_end(args);
    }

    return 0;
}