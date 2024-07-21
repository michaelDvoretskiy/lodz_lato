#include <stdio.h>

union bits_u {
    unsigned char byte;
    struct {
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
        unsigned char bit8 : 1;
    } bits;
};

int main() {
    union bits_u number;
    number.byte = 84;

    printf("Bits: %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu",
           number.bits.bit8, number.bits.bit7, number.bits.bit6, number.bits.bit5,
           number.bits.bit4, number.bits.bit3, number.bits.bit2, number.bits.bit1);
    return 0;
}
