#include <stdio.h>

struct point_t {
    int x;
    int y;
};

int read_point_from_binary_file(struct point_t* p, char* filename) {
    if (filename == NULL || p == NULL) {
        return 1;
    }
    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        return 2;
    }

    int res = fread(p, sizeof(struct point_t), 1, f);
    if (res != 1) {
        fclose(f);
        return 3;
    }
    fclose(f);

    return 0;
}

int main() {
    struct point_t p;
    p.x = 1;
    p.y = 2;
    int save_res = read_point_from_binary_file(&p, "saved_point.bin\0");
    if (save_res == 0) {
        printf("x=%d, y=%d\n", p.x, p.y);
    } else {
        printf("Smth went wrong\n");
    }
    return 0;
}