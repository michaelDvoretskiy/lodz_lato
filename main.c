#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

int main() {
    printf("Choose data type: (0 - int, 1 - float, 2 - point)\n");
    int type;
    if (scanf("%d", &type) != 1) {
        return 1;
    }
    if (type !=0 && type != 1 && type != 2) {
        return 1;
    }
    struct calculator_t* calc = create_calculator(type);
    struct input_output_t* io = create_input_output(type);
    void* input1;
    void* input2;
    if (io->read_input(&input1, &input2) != 0) {
        return 1;
    }

    printf("Choose operation: (0 - add, 1 - sub)\n");
    int oper_type;
    if (scanf("%d", &oper_type) != 1) {
        return 1;
    }
    if (oper_type !=0 && oper_type != 1) {
        return 1;
    }

    void* res;
    if (oper_type == 0) {
        res = calc->add(input1, input2);
    } else {
        res = calc->sub(input1, input2);
    }
    io->show_result(res);

    return 0;
}
