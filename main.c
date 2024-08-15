#include <stdio.h>
#include "stat.h"

int main() {
    int** array_of_numbers;
    int res;

    // в задании Данте нужно было спросить имя файла у пользователя, потом определить его расширение bin или txt
    // и потом на основании этого  вызвать функцию для чтения бинарного или текстового фала
    // мы упрощаем задачу, и сразу читаем файл нужной функцией

    // читаем данные из  бинарного файла
//    res = load("input.bin", &array_of_numbers, fmt_binary);

    // или из текстового
     res = load("input.txt", &array_of_numbers, fmt_text);

    if (res != 0) {
        return 1;
    }
    display(array_of_numbers);
    printf("=================\n");

    struct statistic_t* stat;
    int rows_number = statistics_row(array_of_numbers, &stat);
    if (rows_number < 0) {
        return 1;
    }
    show(stat, rows_number);

    return 0;
}
