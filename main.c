#include <stdio.h>
#include <string.h>

union int_bytes_u {
    int i;
    unsigned char bytes[4];
};

void look_bytes_without_union(int number) {
    unsigned char* byte = (unsigned char*)&number;
    for (int i = 0; i < 4; i++) {
        printf("%d ", *(byte+i));
    }
    printf("\n");
}

void look_bytes_with_union(int number) {
    union int_bytes_u u;
    u.i = number;
    for (int i = 0; i < 4; i++) {
        printf("%d ", *(u.bytes+i));
    }
    printf("\n");
}

int main() {
    int number = 125;
    look_bytes_without_union(number);
    look_bytes_with_union(number);

    look_bytes_without_union(257);
    look_bytes_with_union(125453);

    return 0;
}
