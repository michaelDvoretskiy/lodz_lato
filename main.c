#include <stdio.h>

// длинный код, проще для понимания (на мой взгляд ;) )
int add(int x, int y) {
    int res = 0;
    int sum_carry_bit = 0;

    int bits_number = sizeof(int) * 8;
    for (int i = 0; i < bits_number; i++) {
        int x_last_bit = x & 1;
        int y_last_bit = y & 1;
        int res_bit;
        if (x_last_bit == 1 && y_last_bit == 1) {
            res_bit = sum_carry_bit;
            sum_carry_bit = 1;
        }
        if (x_last_bit != y_last_bit) {
            if (sum_carry_bit == 0) {
                res_bit = 1;
                sum_carry_bit = 0;
            } else {
                res_bit = 0;
                sum_carry_bit = 1;
            }
        }
        if (x_last_bit == 0 && y_last_bit == 0) {
            res_bit = sum_carry_bit;
            sum_carry_bit = 0;
        }
        // двигаем результирующий бит на нужное место
        res_bit = res_bit << i;
        // накладываем на результат
        res = res | res_bit;

        x = x >> 1;
        y = y >> 1;
    }

    return res;
}

// короткий код, сложнее понять, что происходит
int add2(int appl1, int appl2) {
    while (appl2 != 0) {
        int carry = appl1 & appl2;
        appl1 = appl1 ^ appl2;
        appl2 = carry << 1;
    }
    return appl1;
}

int main() {
   int x = 10;
   int y = 15;
   int res = add(x, y);
   printf("%d %d\n", res, add2(x, y));

   return 0;
}
