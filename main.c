#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

union byte_bits {
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
    };
};

void arr_to_bits(const int* bits, union byte_bits* u) {
    u->bit1 = *bits;
    u->bit2 = *(bits+1);
    u->bit3 = *(bits+2);
    u->bit4 = *(bits+3);
    u->bit5 = *(bits+4);
    u->bit6 = *(bits+5);
    u->bit7 = *(bits+6);
    u->bit8 = *(bits+7);
}

void bits_to_arr(int* bits, union byte_bits* u) {
    *bits = u->bit1;
    *(bits+1) = u->bit2;
    *(bits+2) = u->bit3;
    *(bits+3) = u->bit4;
    *(bits+4) = u->bit5;
    *(bits+5) = u->bit6;
    *(bits+6) = u->bit7;
    *(bits+7) = u->bit8;
}

int get_bit(union byte_bits* u, int index) {
    int bits[8];
    bits_to_arr(bits, u);
    return *(bits+index);
}

void set_bit(union byte_bits* u, int index, int value) {
    int bits[8];
    bits_to_arr(bits, u);
    *(bits+index) = value;
    arr_to_bits(bits, u);
}

void show_message(char* message) {
    int i = 0;
    union byte_bits message_symbol;
    int message_symbol_bits[8];
    while (*(message + i) != '\0') {
        message_symbol.byte = *(message + i);
        bits_to_arr(message_symbol_bits, &message_symbol);
        printf("%c %d ", *(message + i), *(message + i));
        for (int j = 7; j >= 0; j--) {
            printf("%d", *(message_symbol_bits+j));
        }
        printf("\n");
        i++;
    }
}

void show_arrays(unsigned char* input, unsigned char* output, int size) {
    union byte_bits input_elem;
    union byte_bits output_elem;
    for (int i = 0; i < size; i++) {
        int input_elem_bits[8];
        input_elem.byte = *(input+i);
        bits_to_arr(input_elem_bits, &input_elem);

        int output_elem_bits[8];
        output_elem.byte = *(output+i);
        bits_to_arr(output_elem_bits, &output_elem);

        printf("%d %hhu ", i, *(input+i));
        for (int j = 7; j >= 0; j--) {
            printf("%d", *(input_elem_bits+j));
        }

        printf(" %hhu ", *(output+i));
        for (int j = 7; j >= 0; j--) {
            printf("%d", *(output_elem_bits+j));
        }

        printf("\n");
    }
}

unsigned char* encode(unsigned char* input, char* message, int array_size) {
    unsigned char* output = malloc(array_size);

    union byte_bits* character_from_message = malloc(sizeof(union byte_bits));
    union byte_bits* character_to_output = malloc(sizeof(union byte_bits));

    int message_current_symbol_num = 0;
    int arr_index = 0;
    int finish = 0;
    while (finish != 1) {
        if (*(message+message_current_symbol_num) == '\0') {
            finish = 1;
        }
        character_from_message->byte = *(message+message_current_symbol_num);
        for (int current_bit = 0; current_bit < 8; current_bit++) {
//        for (int current_bit = 7; current_bit >= 0; current_bit--) {
//            arr_index = message_current_symbol_num * 8 + (7-current_bit);
            arr_index = message_current_symbol_num * 8 + current_bit;
            character_to_output->byte = *(input + arr_index);
            int msg_symbol_bit = get_bit(character_from_message, current_bit);
            set_bit(character_to_output, 0, msg_symbol_bit);
            *(output + arr_index) = character_to_output->byte;
        }
        message_current_symbol_num++;
    }
    for (int i = arr_index + 1; i < array_size; i++) {
        *(output + i) = *(input + i);
    }
    free(character_from_message);
    free(character_to_output);
    return output;
}

unsigned char* decode(unsigned char* input, int array_size) {
    unsigned char* message = malloc(array_size / 8);
    union byte_bits* character_from_input = malloc(sizeof(union byte_bits));
    union byte_bits* character_to_message = malloc(sizeof(union byte_bits));

    int message_current_symbol_num = 0;
    int arr_index = 0;
    int finish = 0;
    while (finish != 1) {
        for (int current_bit = 0; current_bit < 8; current_bit++) {
            arr_index = message_current_symbol_num * 8 + current_bit;
            character_from_input->byte = *(input + arr_index);
            int input_symbol_first_bit = get_bit(character_from_input, 0);
            set_bit(character_to_message, current_bit, input_symbol_first_bit);
        }
        *(message + message_current_symbol_num) = character_to_message->byte;
        message_current_symbol_num++;
        if (character_to_message->byte == '\0') {
            finish = 1;
        }
    }
    free(character_from_input);
    free(character_to_message);

    return message;
}

int main() {
    unsigned char input[] = {1, 54, 124, 34, 21, 43, 243, 231, 3, 2,
                   123, 43, 64, 22, 5, 65, 32, 19, 9, 5,
                   22, 54, 3, 7, 90, 21, 231, 3, 2, 54,
                   35, 44, 1, 78, 213, 176, 198, 34, 28, 82,
                   32, 33, 54, 78, 143, 101, 123, 241, 21, 11};
    int array_size = 50;
    char* message = malloc(array_size / 8);
    strcpy(message, "Hello\0");

    show_message(message);
    printf("==============\n");

    unsigned char* output = encode(input, message, array_size);
    show_arrays(input, output, array_size);
    free(message);

    printf("==============\n");
    unsigned char* message2 = decode(output, array_size);
    printf("%s\n", message2);
    free(message2);
    free(output);
    return 0;
}
