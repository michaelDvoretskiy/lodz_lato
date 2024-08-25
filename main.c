#include <stdio.h>
#include <stdarg.h>

int my_sum(int *res, int num, ...) {
    if (res == NULL){
        return 1;
    }

    if (num <= 0) return 1;

    // специальный тип данных-указатель для перемещения по аргументам функции
    va_list args;
    // устанавливаем указатель на последний параметр перед ...
    // инициализирует указатель args для перемещения по параметрам функции,
    // которые идут после параметра num
    va_start(args, num);

    *res = 0;
    for (int i = 0; i < num; i++) {
        // перемещаем указатель args и читаем данные размером int в переменную next_arg
        int next_arg = va_arg(args, int);
        *res += next_arg;
    }

    // нужно вызвать для коректного завершения работы с args (возможно освобождает память под указатель)
    va_end(args);

    return 0;
}

int main() {
    int sum_value, res;

    res = my_sum(&sum_value, 3, 10, 20, 30);
    if (res == 0) {
        printf("sum: %d\n", sum_value);
    } else {
        return 1;
    }

    // передача элементов массива
    int arr_int[] = {3, 5, -10, 15};
    res = my_sum(&sum_value, 4, *arr_int, *(arr_int+1), *(arr_int+2), *(arr_int+3));
    if (res == 0) {
        printf("sum: %d\n", sum_value);
    } else {
        return 1;
    }

    // такие функции неудобно вызывать для случаев,
    // когда мы не знаем заранее, скольно нужно будет передать аргументов.
    // Например если мы не знаем заранее размер массива.
    // Тут все способы будут в большей или в меньшей степени "карявые" ((

    int arr_size = 4;

    // первый способ - вызываем функцию по разному, в зависимости от количества аргументов
    // этот способ становится неудобным, если возможно большое количество аргументов
    if (arr_size == 1) {
        res = my_sum(&sum_value, arr_size, *arr_int);
    } else if(arr_size == 2) {
        res = my_sum(&sum_value, arr_size, *arr_int, *(arr_int+1));
    } else if(arr_size == 3) {
        res = my_sum(&sum_value, arr_size, *arr_int, *(arr_int+1), *(arr_int+2));
    } else if(arr_size == 4) {
        res = my_sum(&sum_value, arr_size, *arr_int, *(arr_int+1), *(arr_int+2), *(arr_int+3));
    }
    if (res == 0) {
        printf("sum: %d\n", sum_value);
    } else {
        return 1;
    }

    // второй способ - сразу передаем в функцию максимально-возможное количество аргументов,
    // но в "несуществуующие" аргументы передаем NULL
    res = my_sum(
            &sum_value,
            arr_size,
            *arr_int,
            arr_size > 1 ? *(arr_int + 1) : NULL,
            arr_size > 2 ? *(arr_int + 2) : NULL,
            arr_size > 3 ? *(arr_int + 3) : NULL
    );
    if (res == 0) {
        printf("sum: %d\n", sum_value);
    } else {
        return 1;
    }

    // возможно есть более красивый способ передать заранее неизвестное количество аргуметров
    // в такую функцию - я не нашел, просто передать массив целиком похоже нельзя ((

    return 0;
}