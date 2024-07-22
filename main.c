#include <stdio.h>

union int_bytes_u {
    unsigned int i;
    unsigned short s[2];
    unsigned char bytes1[4];
    struct {
        unsigned int byte1 : 8;
        unsigned int byte2 : 8;
        unsigned int byte3 : 8;
        unsigned int byte4 : 8;
    } bytes2;
    struct {
        unsigned int bit_1 : 1;
        unsigned int bit_2 : 1;
        unsigned int bit_3 : 1;
        unsigned int bit_4 : 1;
        unsigned int bit_5 : 1;
        unsigned int bit_6 : 1;
        unsigned int bit_7 : 1;
        unsigned int bit_8 : 1;
        unsigned int bit_9 : 1;
        unsigned int bit_10 : 1;
        unsigned int bit_11 : 1;
        unsigned int bit_12 : 1;
        unsigned int bit_13 : 1;
        unsigned int bit_14 : 1;
        unsigned int bit_15 : 1;
        unsigned int bit_16 : 1;
        unsigned int bit_17 : 1;
        unsigned int bit_18 : 1;
        unsigned int bit_19 : 1;
        unsigned int bit_20 : 1;
        unsigned int bit_21 : 1;
        unsigned int bit_22 : 1;
        unsigned int bit_23 : 1;
        unsigned int bit_24 : 1;
        unsigned int bit_25 : 1;
        unsigned int bit_26 : 1;
        unsigned int bit_27 : 1;
        unsigned int bit_28 : 1;
        unsigned int bit_29 : 1;
        unsigned int bit_30 : 1;
        unsigned int bit_31 : 1;
        unsigned int bit_32 : 1;
    };
};

int main() {
    union int_bytes_u u;
    u.i = 24042;
    printf("%u\n", u.i);

    printf("%hu %hu\n", u.s[0], u.s[1]);

    for (int i = 0; i < 4; i++) {
        printf("%hhu ", u.bytes1[i]);
    }
    printf("\n");

    printf("%hhu %hhu %hhu %hhu\n", u.bytes2.byte1, u.bytes2.byte2, u.bytes2.byte3, u.bytes2.byte4);

    printf("%u%u%u%u%u%u%u%u %u%u%u%u%u%u%u%u %u%u%u%u%u%u%u%u %u%u%u%u%u%u%u%u\n",
           u.bit_8, u.bit_7, u.bit_6, u.bit_5,
           u.bit_4, u.bit_3, u.bit_2, u.bit_1,
           u.bit_16, u.bit_15, u.bit_14, u.bit_13,
           u.bit_12, u.bit_11, u.bit_10, u.bit_9,
           u.bit_24, u.bit_23, u.bit_22, u.bit_21,
           u.bit_20, u.bit_19, u.bit_18, u.bit_17,
           u.bit_32, u.bit_31, u.bit_30, u.bit_29,
           u.bit_28, u.bit_27, u.bit_26, u.bit_25);

    return 0;
}
