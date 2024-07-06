#include <stdio.h>
#include <stdlib.h>

int main() {
    char* baseString = "Hello\0";
    char* result = malloc(10);
    for (int baseNumber = 0; baseNumber < 10; baseNumber++) {
        sprintf(result, "%s %d !", baseString, baseNumber);

        printf("%s\n", result);
    }
    return 0;
}
