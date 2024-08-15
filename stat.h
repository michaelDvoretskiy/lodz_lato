#ifndef CODE_STAT_H
#define CODE_STAT_H

enum save_format_t {
    fmt_text,
    fmt_binary
};

struct statistic_t {
    int min;
    int max;
};

// в функцию передаем двумерный массив целых чисел int** ptr,
// в каждой строке которого (одномерном массиве) будем искать минимальное и максимальное значение
// для каждой стоки массива int** ptr создаем struct statistic_t и записываем туда min и max значение
// т.е. в результате получаем одномерный массив struct statistic_t*
// но вызывая функцию, будем передавать ссылку на этот массив через &
// поэтому stats идет не с одной * а с двумя  **
// Например на входе двумерный массив
// 5 4 7 10
// 3 90 65 8
// 51 18 52 12
// На выходе будет
// {min: 4, max: 10} {min: 3, max: 90} {min: 12, max: 52}
// в задании Данте нужно было посчитать еще другие статистические данные, мы оставили только min и max
int statistics_row(int** ptr, struct statistic_t** stats);

// освобождение памяти двумерного массива int** ptr,
// но передавать его будем из main-а, как ссылку &
// поэтому не 2 звездочки **, и 3 ***
void destroy(int*** ptr);

// вывод на экран двумерного массива int** ptr
void display(int** ptr);

// загрузка из файла char* filename в массив двумерный int** ptr
// но передавать его будем из main-а, как ссылку &
// поэтому не 2 звездочки **, и 3 ***
// enum save_format_t format - тип файла, из которого будем читать
// fmt_text - текстовый
// fmt_binary - бинарный
int load(const char* filename, int*** ptr, enum save_format_t format);

// вывод на экран статистику
void show(struct statistic_t* stats, int size);

#endif //CODE_STAT_H
