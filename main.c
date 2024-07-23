#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ROWS 8
#define COLUMNS 40

union bit_set_u {
    unsigned char byte;
    struct {
        unsigned char bit_1 : 1;
        unsigned char bit_2 : 1;
        unsigned char bit_3 : 1;
        unsigned char bit_4 : 1;
        unsigned char bit_5 : 1;
        unsigned char bit_6 : 1;
        unsigned char bit_7 : 1;
        unsigned char bit_8 : 1;
    };
};

void bit_set_to_array(union bit_set_u u, unsigned char* bits) {
    *bits = u.bit_1;
    *(bits+1) = u.bit_2;
    *(bits+2) = u.bit_3;
    *(bits+3) = u.bit_4;
    *(bits+4) = u.bit_5;
    *(bits+5) = u.bit_6;
    *(bits+6) = u.bit_7;
    *(bits+7) = u.bit_8;
}

char* prepare_to_display(const uint8_t* bytes) {
    int bits_number = ROWS * COLUMNS;
    int bytes_number = bits_number / 8;
    int new_line_char_number = ROWS;
    int string_len = bits_number + new_line_char_number + 1;
    char* out = malloc(string_len);
    if (out == NULL) {
        return NULL;
    }

    union bit_set_u bit_set;
    unsigned char* bits = malloc(8);
    int current_column = 0;
    int current_symbol = 0;
    for (int i = 0; i < bytes_number; i++) {
        bit_set.byte = *(bytes + i);
        bit_set_to_array(bit_set, bits);

        for (int j = 8; j > 0; j--) {
            *(out+current_symbol) = *(bits + j) == 1 ? '#' : ' ';
            current_column++;
            current_symbol++;

            if (current_column == COLUMNS) {
                *(out+current_symbol) = '\n';
                current_symbol++;
                current_column = 0;
            }
        }
        *(out+current_symbol) = '\0';
    }
    return out;
}

int main() {
    uint8_t *bmp = (uint8_t *)malloc(ROWS * COLUMNS);
    if (bmp == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter values:");
    for (int i = 0; i < ROWS * (COLUMNS / 8); i++) {
        if (scanf("%hhx", bmp+i) != 1) {
            printf("Incorrect input\n");
            free(bmp);
            return 1;
        }
    }

    char* out = prepare_to_display(bmp);
    printf("%s", out);

    free(bmp);
    free(out);

    return 0;
}
