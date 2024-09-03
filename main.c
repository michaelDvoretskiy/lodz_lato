#include <stdio.h>
#include <stdlib.h>

// проходим все биты и считаем единицы и нули
int check_ones_more_then(int value, int limit) {
    int number_of_bits = sizeof(value) * 8;
    int ones = 0;
    for (int i = 0; i < number_of_bits; i++) {
        int last_bit_value = value & 1;
        if (last_bit_value == 1) {
            ones++;
        }
        value = value >> 1;
    }
//    можно раскометрировать, чтобы проверить,  сколько нулей и единиц в числе
//    printf("%d %d\n", ones, zeros);
    if (ones > limit) {
        return 1;
    }
    return 0;
}

// считаем единицы, пока не 0
int check_ones_more_then2(int value, int limit) {
    int ones = 0;
    while (value != 0) {
        int last_bit_value = value & 1;
        ones += last_bit_value;
        value = value >> 1;
    }
//    printf("%d\n", ones);
    if (ones > limit) {
        return 1;
    }
    return 0;
}

int main() {
    int numbers_count;
    int number;

    int good_numbers_count = 0;
    int* good_numbers = malloc(sizeof(int));

    int ones_limit = 0;

    printf("Enter quantity of numbers:\n");
    if (scanf("%d", &numbers_count) != 1) {
        return 1;
    }

    printf("Enter number of ones limit:\n");
    if (scanf("%d", &ones_limit) != 1) {
        return 1;
    }

    printf("Enter numbers:\n");
    for (int i = 0; i < numbers_count; i++) {
        if (scanf("%d", &number) != 1) {
            return 1;
        }

        if (check_ones_more_then(number, ones_limit)) {
            good_numbers_count++;
            if (good_numbers_count > 1) {
                int* tmp_good_numbers = realloc(good_numbers, good_numbers_count * sizeof(int));
                if (tmp_good_numbers == NULL) {
                    free(good_numbers);
                    return 1;
                }
                good_numbers = tmp_good_numbers;
            }

            *(good_numbers + good_numbers_count - 1) = number;
        }
    }

    for (int i = 0; i < good_numbers_count; i++) {
        printf("%d ", *(good_numbers + i));
    }
    printf("\n");

    free(good_numbers);
}
