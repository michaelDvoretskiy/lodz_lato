#include <stdio.h>

struct point_t {
    int x;
    int y;
};

int write_point_to_binary_file(struct point_t* p, char* filename) {
    if (filename == NULL || p == NULL) {
        return 1;
    }
    FILE* f = fopen(filename, "wb");
    if (f == NULL) {
        return 2;
    }

    int res = fwrite(p, sizeof(struct point_t), 1, f);
    if (res != 1) {
        fclose(f);
        return 3;
    }
    fclose(f);

    return 0;
}

int main() {
    struct point_t p;
    p.x = 10;
    p.y = 20;
    int save_res = write_point_to_binary_file(&p, "saved_point.bin\0");
    if (save_res == 0) {
        printf("Saved\n");
    } else {
        printf("Smth went wrong\n");
    }
    return 0;
}