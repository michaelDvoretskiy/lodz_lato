#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int res;
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        res = rand() % 1001;
        printf("%d\n", res);
    }

    return 0;
}
