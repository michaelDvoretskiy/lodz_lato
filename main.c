#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bank_t {
    char* name;
};

void destroy_banks(struct bank_t* banks, int number_of_banks) {
    if (banks == NULL) {
        return;
    }
    for (int i = 0; i < number_of_banks; i++) {
        if ((banks+i)->name != NULL) {
            free((banks + i)->name);
        }
    }
    free(banks);
    banks = NULL;
}

void show_banks(struct bank_t* banks, int number_of_banks) {
    if (banks == NULL || number_of_banks <= 0) {
        return;
    }
    printf("BANKS:\n");
    for (int i = 0; i < number_of_banks; i++) {
        printf("%s\n", (banks+i)->name);
    }
}

void add_bank_wrong(struct bank_t* banks, int numb_of_banks, char* name) {

    printf("Try to allocate %d\n", sizeof(struct bank_t) * (numb_of_banks+1));
    struct bank_t* new_banks = (struct bank_t*)realloc(banks, sizeof(struct bank_t) * (numb_of_banks + 1));
    printf("good!\n");
    banks = new_banks;

    (banks + numb_of_banks)->name = (char*)malloc(31);
    strcpy((banks + numb_of_banks)->name, name);
}

void add_bank(struct bank_t** banks, int numb_of_banks, char* name) {

    printf("Try to allocate %d\n", sizeof(struct bank_t) * (numb_of_banks+1));
    struct bank_t* new_banks = (struct bank_t*)realloc(*banks, sizeof(struct bank_t) * (numb_of_banks + 1));
    printf("good!\n");
    *banks = new_banks;

    (*banks + numb_of_banks)->name = (char*)malloc(31);
    strcpy((*banks + numb_of_banks)->name, name);
}

int main() {
    int number_of_banks = 0;

    struct bank_t* banks = (struct bank_t*)malloc(sizeof(struct bank_t));
    if (banks == NULL) {
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        char* bank_name = malloc(31);
        sprintf(bank_name, "%s_%d", "Bank", i);
        add_bank(&banks,  i, bank_name);
//        add_bank_wrong(banks,  i, bank_name);
        number_of_banks = i+1;
    }
    show_banks(banks, number_of_banks);

    destroy_banks(banks, number_of_banks);

    return 0;
}
