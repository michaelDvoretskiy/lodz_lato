#include <stdio.h>

int main() {
    unsigned short u_short_num = 345;
    printf("%llu %hu\n", sizeof(unsigned short), u_short_num);

    short short_num = -50;
    printf("%llu %hu\n", sizeof(short), short_num);

    unsigned int u_num = 120;
    printf("%llu %u\n", sizeof(unsigned int), u_num);

    int num = -234;
    printf("%llu %d\n", sizeof(int), num);

    unsigned long int u_l_num = 2342;
    printf("%llu %lu\n", sizeof(unsigned long int), u_l_num);

    long int l_num = -2342;
    printf("%llu %ld\n", sizeof(long int), l_num);

    unsigned long long int u_ll_num = 2342;
    printf("%llu %llu\n", sizeof(unsigned long long int), u_ll_num);

    long long int ll_num = -2342;
    printf("%llu %lld\n", sizeof(long long int), ll_num);

    return 0;
}
