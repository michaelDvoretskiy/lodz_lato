#ifndef CODE_FUNCTIONS_H
#define CODE_FUNCTIONS_H
#include <stdio.h>

#define CREATE_FUNCTIONS(TYPE, FORMAT)       \
TYPE read_##TYPE(TYPE* value, int size) {    \
    printf("Enter %d values\n", size);       \
    for (int i = 0; i < size; i++) {         \
        if (scanf(FORMAT, value+i) != 1) {   \
            return 1;                        \
        }                                    \
    }                                        \
    return 0;                                \
}                                            \
                                             \
int display_##TYPE(TYPE* value, int size) {  \
    for (int i = 0; i < size; i++) {         \
       printf(FORMAT, *(value + i));         \
       printf(" ");                          \
    }                                        \
    printf("\n");                            \
    return 0;                                \
}

CREATE_FUNCTIONS(int, "%d");
CREATE_FUNCTIONS(float, "%f");

#endif //CODE_FUNCTIONS_H
