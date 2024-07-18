#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct bank_t {
    char* name;
};

struct card_t {
    struct bank_t* bank;
    char* title;
    int remain;
};

void read_eol() {
    char ch;
    scanf("%c", &ch);
    while (ch != '\n') {
        scanf("%c", &ch);
    }
}

int read_data_from_console(char* card_title, char* bank_name) {
    printf("Enter the card title:");
    int scan_res = scanf("%s", card_title);
    if (scan_res != 1) {
        return 1;
    }
    size_t line_break_index = strcspn(card_title, "\n");
    *(card_title+line_break_index) = '\0';

    printf("Enter the bank name:");
    scan_res = scanf("%s", bank_name);
    if (scan_res != 1) {
        return 1;
    }
    line_break_index = strcspn(bank_name, "\n");
    *(bank_name+line_break_index) = '\0';

    return 0;
}

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

void destroy_cards(struct card_t* cards, int number_of_cards) {
    if (cards == NULL) {
        return;
    }
    for (int i = 0; i < number_of_cards; i++) {
        if ((cards+i)->title != NULL) {
            free((cards + i)->title);
        }
    }
    free(cards);
    cards = NULL;
}

void show_cards(struct card_t* cards, int number_of_cards) {
    if (cards == NULL || number_of_cards <= 0) {
        return;
    }
    printf("CARDS:\n");
    for (int i = 0; i < number_of_cards; i++) {
        printf("card %s, bank %s, remain %d\n", (cards+i)->title, (cards+i)->bank->name, (cards+i)->remain);
    }
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

struct bank_t* get_bank(struct bank_t** banks, int* number_of_banks, char* bank_name) {
    if (number_of_banks == NULL || bank_name == NULL || banks == NULL) {
        return NULL;
    }
    if (*banks == NULL && *number_of_banks > 0) {
        return NULL;
    }

    int numb_of_banks = *number_of_banks;

    if (numb_of_banks != 0) {
        for (int i = 0; i < numb_of_banks; i++) {
            if (strcmp(bank_name, (*banks+i)->name) == 0) {
                return *banks+i;
            }
        }
        struct bank_t* new_banks = (struct bank_t*)realloc(*banks, sizeof(struct bank_t) * (numb_of_banks + 1));
        if (new_banks == NULL) {
            printf("Failed to allocate memory");
            return NULL;
        }
        *banks = new_banks;
    }

    (*banks + numb_of_banks)->name = (char*)malloc(31);
    if ((*banks + numb_of_banks)->name == NULL) {
        printf("Failed to allocate memory");
        return NULL;
    }
    strcpy( (*banks + numb_of_banks)->name,  bank_name);

    numb_of_banks++;
    *number_of_banks = numb_of_banks;

    return *banks + (numb_of_banks - 1);
}

struct card_t* add_card(struct card_t** cards, int* number_of_cards, char* card_title, struct bank_t* bank) {
    if (number_of_cards == NULL || card_title == NULL || bank == NULL || cards == NULL) {
        return NULL;
    }
    if (*cards == NULL && *number_of_cards > 0) {
        return NULL;
    }

    int numb_of_cards = *number_of_cards;

    if (numb_of_cards != 0) {
        struct card_t* new_cards = (struct card_t*)realloc(*cards, sizeof(struct card_t) * (numb_of_cards+1));
        if (new_cards == NULL) {
            printf("Failed to allocate memory");
            return NULL;
        }
        *cards = new_cards;
    }

    (*cards + numb_of_cards)->title = malloc(31);
    if ((*cards + numb_of_cards)->title == NULL) {
        printf("Failed to allocate memory");
        return NULL;
    }
    strcpy((*cards + numb_of_cards)->title, card_title);
    (*cards + numb_of_cards)->bank = bank;
    (*cards + numb_of_cards)->remain = 0;

    numb_of_cards++;
    *number_of_cards = numb_of_cards;

    return (*cards + numb_of_cards - 1);
}

int top_up_account(struct card_t** cards, int number_of_cards, int amount) {
   if (cards == NULL || *cards == NULL || amount <= 0) {
       return 1;
   }
   int min_remain = (*cards)->remain;
   struct card_t* card = *cards;
   for (int i = 0; i < number_of_cards; i++) {
       if ((*cards+i)->remain < min_remain) {
           min_remain = (*cards+i)->remain;
           card = *cards+i;
       }
   }
   card->remain += amount;
   return 0;
}

int main() {
    int number_of_banks = 0;
    int number_of_cards = 0;

    struct bank_t* banks = (struct bank_t*)malloc(sizeof(struct bank_t));
    if (banks == NULL) {
        return 1;
    }

    struct card_t* cards = (struct card_t*)malloc(sizeof(struct card_t)*10);
    if (cards == NULL) {
        destroy_cards(cards, number_of_cards);
        return 1;
    }

    char* card_title = malloc(31);
    if (card_title == NULL) {
        destroy_banks(banks, number_of_banks);
        destroy_cards(cards, number_of_cards);
        printf("Failed to allocate memory\n");
        return 1;
    }

    char* bank_name = malloc(31);
    if (bank_name == NULL) {
        destroy_banks(banks, number_of_banks);
        destroy_cards(cards, number_of_cards);
        free(card_title);
        printf("Failed to allocate memory\n");
        return 1;
    }

    while(1) {
        int read_data_res = read_data_from_console(card_title, bank_name);
        if (read_data_res == 1) {
            printf("Smth went wrong");
            return 1;
        }
        struct bank_t* bank = get_bank(&banks,  &number_of_banks, bank_name);
        if (bank == NULL) {
            printf("Smth went wrong");
            free(card_title);
            free(bank_name);
            destroy_banks(banks, number_of_banks);
            destroy_cards(cards, number_of_cards);
            return 2;
        }

        struct card_t* card = add_card(&cards, &number_of_cards, card_title, bank);
        if (card == NULL) {
            free(card_title);
            free(bank_name);
            destroy_banks(banks, number_of_banks);
            destroy_cards(cards, number_of_cards);
            return 3;
        }

        read_eol();

        printf("Finish Y/N ?");
        char answer;
        scanf("%c", &answer);
        if (answer == 'y') {
            break;
        }
    }

    show_cards(cards, number_of_cards);
    show_banks(banks, number_of_banks);

    srand(time(NULL));
    for (int i = 1; i < 10; i++) {
        int amount = rand() % 1001;
        printf("\nadding %d\n", amount);
        top_up_account(&cards, number_of_cards, amount);
        show_cards(cards, number_of_cards);
    }

    destroy_banks(banks, number_of_banks);
    destroy_cards(cards, number_of_cards);

    return 0;
}