#include <stdio.h>
#include <stdarg.h>

void display_template(char* template, ...) {
    va_list args;
    va_start(args, template);

    while (*template) {
        if (*template != '?') {
            printf("%c", *template);
        } else {
            char* param = va_arg(args, char*);
            printf("%s", param);
        }
        template++;
    }

    va_end(args);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Not enough arguments\n");
        return 1;
    }

    display_template( *(argv + 1),
                      argc > 2 ? *(argv + 2) : NULL,
                      argc > 3 ? *(argv + 3) : NULL,
                      argc > 4 ? *(argv + 4) : NULL,
                      argc > 5 ? *(argv + 5) : NULL,
                      argc > 6 ? *(argv + 6) : NULL,
                      argc > 7 ? *(argv + 7) : NULL,
                      argc > 8 ? *(argv + 8) : NULL,
                      argc > 9 ? *(argv + 9) : NULL,
                      argc > 10 ? *(argv + 10) : NULL,
                      argc > 11 ? *(argv + 11) : NULL
                      );

    return 0;
}
