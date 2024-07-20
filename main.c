#include <stdio.h>
#include <stddef.h>

struct message_t {
    char a;
    double b;
    int c;
};

void show_sizes(struct message_t* m) {
    printf("char %d, double %d, int %d, struct message_t* %d, struct message_t %d\n", sizeof(char), sizeof(double), sizeof(int), sizeof(struct message_t*), sizeof(struct message_t));
    printf("char variable %d, double variable %d, int variable %d, struct message_t* variable %d, struct message_t variable %d\n", sizeof(m->a), sizeof(m->b), sizeof(m->c), sizeof(m), sizeof(*m));
}

void show_areas() {
    printf("Offset of a: %zu, size a: %d\n", offsetof(struct message_t, a), sizeof(char));
    printf("Offset of b: %zu, size b: %d\n", offsetof(struct message_t, b), sizeof(double));
    printf("Offset of c: %zu, size c: %d\n", offsetof(struct message_t, c), sizeof(int));
    printf("Size of struct: %zu\n", sizeof(struct message_t));
}

int field_number(int byte_number) {
    if (byte_number >= offsetof(struct message_t, a) && byte_number < offsetof(struct message_t, a) + sizeof(char)) {
        return 1;
    }
    if (byte_number >= offsetof(struct message_t, b) && byte_number < offsetof(struct message_t, b) + sizeof(double)) {
        return 2;
    }
    if (byte_number >= offsetof(struct message_t, c) && byte_number < offsetof(struct message_t, c) + sizeof(int)) {
        return 3;
    }
    return 0;
}

void show_bytes(struct message_t* m) {
    int bytes_quantity = sizeof(struct message_t);
    char* byte = (char*)m;
    for (int i = 0; i < bytes_quantity; i++) {
        printf("%d %d %d %d\n", i, byte+i, *(byte+i), field_number(i));
    }
    printf("\n");
}

int main() {
    struct message_t m;
    m.a = 'y';
    m.b = 10.25f;
    m.c = 1000;

    show_sizes(&m);
    printf("==========\n");
    show_areas();
    printf("==========\n");
    show_bytes(&m);

    return 0;
}
