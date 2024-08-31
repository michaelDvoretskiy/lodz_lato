#include "print.h"

int main() {
    double d_val = 10.44;
    int i_val = 20;
    int res = my_printf("%d %f %a %f", i_val, d_val, 25.43);
    if (res !=0) {
        return 1;
    }

    return 0;
}
