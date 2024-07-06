#include <stdio.h>
#include <string.h>

int return_and_maybe_exit(char* fun_name, int status, int *res) {
    *res = 0;
    if (strcmp(fun_name, "my_fun_1\0") == 0 && status == 1) {
        printf("Incorrect input data\n");
        *res = 1;
        return 5;
    }
    if (strcmp(fun_name, "my_fun_1\0") == 0 && status == 2) {
        printf("Incorrect input\n");
        return 6;
    }
    if (strcmp(fun_name, "my_fun_2\0") == 0 && status == 1) {
        printf("Smth went wrong\n");
        *res = 1;
        return 3;
    }
    if (strcmp(fun_name, "my_fun_2\0") == 0 && status == 2) {
        printf("Incorrect input\n");
        return -3;
    }
    if (strcmp(fun_name, "my_fun_3\0") == 0 && status > 0) {
        printf("Quantity from my_fun_3 - %d\n", status);
        *res = 1;
        return status;
    }
    return 0;
}

int my_fun_1(int par) {
    return par;
}

void my_fun_2(int *err) {
    *err = 2;
}

int my_fun_3(int par) {
    if (par > 0) {
        return par;
    }
    return 0;
}

int main() {
    int program_status = 0, program_exit = 0, fun_status = 0;

    fun_status = my_fun_1(2);
    program_status = return_and_maybe_exit("my_fun_1\0", fun_status, &program_exit);
    if (program_exit == 1) {
        return program_status;
    }

    my_fun_2(&fun_status);
    program_status = return_and_maybe_exit("my_fun_2\0", fun_status, &program_exit);
    if (program_exit == 1) {
        return program_status;
    }

    fun_status = my_fun_3(10);
    program_status = return_and_maybe_exit("my_fun_3\0", fun_status, &program_exit);
    if (program_exit == 1) {
        return program_status;
    }

    printf("after all");

    return 0;
}
