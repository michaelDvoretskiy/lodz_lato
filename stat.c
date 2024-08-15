#include <stdio.h>
#include <stdlib.h>
#include "stat.h"

void display(int **ptr) {
    if (ptr == NULL) {
        return;
    }
    int row = 0, col = 0;
    // = NULL - это признак последней строки
    while (*(ptr + row) != NULL) {
        // = -1 - это признак последнего элемента в строке
        while (*(*(ptr + row) + col) != -1) {
            printf("%d ", *(*(ptr + row) + col));
            col++;
        }
        printf("\n");
        col = 0;
        row++;
    }
}

void destroy(int ***ptr) {
    if (*ptr != NULL) {
        int row = 0;

        // освобождаем массив-строку
        while (*((*ptr) + row) != NULL) {
            free(*((*ptr) + row));
            *((*ptr) + row) = NULL;
            row++;
        }

        // освобожнаем массив строк (массив массивов)
        free(*ptr);
        *ptr = NULL;
    }
}

int statistics_row(int** ptr, struct statistic_t** stats) {
    if (ptr ==NULL || stats == NULL) {
        return -1;
    }

    // считаем количество строк в массиве чисел,
    // чтобы выделить память под такое же количество элементов в массиве *stats
    int rows = 0;
    while (*(ptr + rows) != NULL) {
        rows++;
    }

    // stats - это ссылка на массив структур, мы передаем  ее через &,
    // поэтому сам массив - это *stats
    // выделяем память под него, количество элементов - это количество строк в массиве чисел
    *stats = malloc(rows * sizeof(struct statistic_t));
    if (*stats == NULL) {
        return -2;
    }

    // для каждой строки заполняем статистику
    for (int i = 0; i < rows; i++) {
        int col = 0;

        // если количество элементов в строке 0, то по условию min и max должны быть равны -1
        (*((*stats)+i)).min = -1;
        (*((*stats)+i)).max = -1;

        // идем по элементам строки, пока не встретим -1 (признак последнего элемента)
        while (*(*(ptr + i) + col) != -1) {
            int val = *(*(ptr + i) + col);
            // если это первый елемент строки - записываем его значение в максимальное и минимальное
            if (col == 0) {
                (*((*stats) + i)).min = val;
                (*((*stats) + i)).max = val;
            }

            // дальше проверяем, если меньше минимального - в минимальное
            if (val < (*((*stats) + i)).min) (*((*stats) + i)).min = val;
            // если больше максимального - в максимальное
            if (val > (*((*stats) + i)).max) (*((*stats) + i)).max = val;

            col++;
        }
    }

    return rows;
}

void show(struct statistic_t* stats, int size) {
    if (stats == NULL) {
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("row %d: min=%d max=%d\n", i+1, (stats+i)->min, (stats+i)->max);
    }
}