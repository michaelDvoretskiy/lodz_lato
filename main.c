#include <stdio.h>
#include "list.h"

int main() {
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("cannot open file\n");
        return 1;
    }

    char buf[1024];
    while (!feof(f)) {
        int status = read_line(f, buf);
        if (status != 0) {
            printf("cannot read the line\n");
            return 1;
        }
        printf("%s\n", buf);
    }

    fclose(f);
    return 0;
}
