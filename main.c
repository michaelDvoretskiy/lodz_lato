#include <stdio.h>

void read_eol() {
    char ch;
    scanf("%c", &ch);
    while (ch != '\n') {
        scanf("%c", &ch);
    }
}

int main() {
    char input[30];
    printf("Enter value:");
    // читаємо рядок "за раз", але в цьому випалку не дочитується \n
    scanf("%30s", input);
    printf("You have entered %s\n", input);

    read_eol();
    // якщо не викликати read_eol, то просто дочитається минулий \n
    // і користувацький ввод сприйметься, як порожній рядок
    printf("Enter one more value:");
    char ch;
    int current_symbol_number = 0;
    // читаємо рядок посимвольрно, поки не кінець рядку \n
    scanf("%c", &ch);
    while (ch != '\n') {
        *(input + current_symbol_number) = ch;
        current_symbol_number++;
        scanf("%c", &ch);
    }
    *(input + current_symbol_number) = '\0';
    printf("You have entered %s\n", input);

    return 0;
}
