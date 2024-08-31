#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "print.h"

int my_print_one_int(void* value) {
    int num = *((int*) value);

    if (num < 0) {
        putchar('-');
        num = -num;
    }
    if (num == 0) {
        putchar('0');
        return 0;
    }

    // int не может быть длиннее 12 символов
    char* digits = malloc(sizeof(char) * 12);
    if (digits == NULL) {
        return 1;
    }

    int digitIndex = 0;
    while (num > 0) {
        *(digits + digitIndex) = (num % 10) + '0';
        num /= 10;
        digitIndex++;
    }

    for (int i = digitIndex - 1; i >= 0; i--) {
        putchar(*(digits + i));
    }
    free(digits);

    return 0;
}

int my_print_one_double(void* value) {
    double num = *((double*) value);

    int intPart = (int) num;
    my_print_one_int(&intPart);

    putchar('.');

    double fracPart = num - intPart;
    if (fracPart < 0) {
        fracPart *= -1;
    }
    // печатаем только первые 5 знаков после запятой
    for (int i = 0; i < 5; i++) {
        fracPart *= 10;
        int digit = (int) fracPart;
        putchar(digit + '0');
        fracPart -= digit;
    }

    return 0;
}

int my_print_one_parameter(char type, void* value) {
    int (*my_printer[2])(void* value) = {my_print_one_int, my_print_one_double};
    if (type == 'd') {
        return my_printer[0](value);
    }
    if (type == 'f') {
        return my_printer[1](value);
    }
    return 0;
}

int my_printf(char* format, ...) {
    char *p = format;

    va_list args;
    va_start(args, format);

    int one_print_res = 0;

    while (*p) {
        if (*p == '%') {
            p++;
            switch (*p) {
                case 'd': {
                    int num = va_arg(args, int);
                    one_print_res = my_print_one_parameter(*p, &num);
                    if (one_print_res != 0) {
                        return one_print_res;
                    }
                    break;
                }
                case 'f': {
                    double num = va_arg(args, double);
                    one_print_res = my_print_one_parameter(*p, &num);
                    if (one_print_res != 0) {
                        return one_print_res;
                    }
                    break;
                }
                default:
                    putchar('%');
                    putchar(*p);
            }
        } else {
            putchar(*p);
        }
        p++;
    }

    va_end(args);

    return 0;
}