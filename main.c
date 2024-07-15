#include <stdio.h>

struct point_t {
    int x;
    int y;
};

int save_point_to_text_file(struct point_t* p, char* filename) {
    if (filename == NULL || p == NULL) {
        return 1;
    }
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        return 2;
    }
    fprintf(f, "%d %d", p->x, p->y);
    // можна також спробувати перевірити успішність запису даних,
    // але не знаю, що тут може піти не так
//    int res = fprintf(f, "%d %d", p->x, p->y);
//    if (res < 0) {
//        fclose(f);
//        return 3;
//    }
    fclose(f);

    return 0;
}

int main() {
    struct point_t p;
    p.x = 10;
    p.y = 20;
    int save_res = save_point_to_text_file(&p, "saved_point.txt\0");
    if (save_res == 0) {
        printf("Saved");
    } else {
        printf("Smth went wrong");
    }
    return 0;
}
