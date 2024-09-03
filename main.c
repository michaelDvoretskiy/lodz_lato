#include <stdio.h>

// макрос будет содержать несколько строк, в том числе объявление переменных
// помним, что макрос - не функциия, произойдет подстановка этого кода туда, гдя мы его вызовем
// поэтому при подстановке может возникнуть конфликт имен переменных,
// если у нас будет накая же внешнем коде. Поэтому делаем "финт ушами", "заворачиваем" код макроса
// в бутафорский цикл do {} while(0), который будет выполнен ровно 1 раз (но это типа не обязательно)
//
#define DISPLAY(value, type) do { \
    int count_of_bits = sizeof(type) * 8;            \
    for (int i = count_of_bits - 1; i >= 0 ; i--) {  \
        int bit = (value >> i) & 1;                  \
        printf("%d", bit);                           \
    }                                                \
    printf("\n");                                    \
} while(0)

// тут мы не делали do {} while(0), и так тоже работает
// но так мы не сможем так вызвать REVERSE в коде больше 1 раза
// т.к. тогда переменная "count_of_bits" будет объявлена более 1-го раза
#define REVERSE(value, type, result) \
    result = 0;                                      \
    int count_of_bits = sizeof(type) * 8;            \
    for (int i = count_of_bits - 1; i >= 0 ; i--) {  \
        int bit = (value >> i) & 1;                  \
        bit = bit << (count_of_bits - i - 1);        \
        result = result | bit;                       \
    }

int main() {
    char number = 10;
    // если мы назовем переменную "number", так, как называется какая то из переменных внутри "DISPLAY",
    // код может работать неправильно
    DISPLAY(number, char);

    char number2;
    REVERSE(number, char, number2);
    DISPLAY(number2, char);

    return 0;
}
