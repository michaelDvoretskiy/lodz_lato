#include <stdio.h>
#include "calc.h"

int main() {
    double d_val = 10.44;
    int i_val = 20;
    double res;
    struct point_t p;
    p.x = 2;
    p.y = 3;

    int status = calculate("d - f * p", &res, i_val, d_val, p);
    if (status != 0) {
        return 1;
    }
    printf("%f\n", res);

    return 0;
}
