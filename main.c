#include <stdio.h>

struct point_t {
    int x;
    int y;
};

int read_point_from_text_file(struct point_t* p, char* filename) {
    if (filename == NULL || p == NULL) {
        return 1;
    }
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        return 2;
    }

    int res = fscanf(f, "%d %d", &(p->x), &(p->y));
    if (res != 2) {
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
    int save_res = read_point_from_text_file(&p, "saved_point.txt\0");
    if (save_res == 0) {
        printf("x=%d, y=%d\n", p.x, p.y);
    } else {
        printf("Smth went wrong\n");
    }
    return 0;
}