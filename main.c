#include <stdio.h>

int main() {
    int int_val = 10;
    float float_val = 10.5f;

    // указатель на int, туда можем записать только адрес памяти,
    // по которому лежит int
    int* ptr_int = &int_val;
    printf("%d\n", *ptr_int);

    // указатель на float, туда можем записать только адрес памяти,
    // по которому лежит float
    float* ptr_float = &float_val;
    printf("%f\n", *ptr_float);

    // а так нельзя, будет ошибка
    // ptr_int = &float_val;
    // ptr_float = &int_val;

    // тип void* представляет собой обобщенный указатель.
    // Указатель типа void* может указывать на данные любого типа,
    void* ptr_void = &int_val;
    ptr_void = &float_val;

    // но сам по себе void* не предоставляет информации о типе данных, на который указывает
    // поэтому так нельзя, т.к. неизвестно, какой тип данных нужно 'достать' из указателя
    // printf("%d", *ptr_void);
    // и так тоже нельзя, по той же причине
    // printf("%f", *ptr_void);

    // перед использованием значения, записанного в таком указателе
    // нужно превратить его в указатель на конкретный тиип данных
    ptr_void = &int_val;
    int* ptr_void_int = (int*)ptr_void;
    printf("%d\n", *ptr_void_int);

    // или так
    ptr_void = &float_val;
    printf("%f\n", *((float*)ptr_float));

    // а зачем это нам может пригодиться - см. в следующем задании

    return 0;
}
