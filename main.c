#include <stdio.h>
#include <stdlib.h>

struct point_t {
    int x;
    int y;
};

int main() {
    int points_quantity;
    printf("Enter number of points:");
    int scan_res = scanf("%d", &points_quantity);

    if (scan_res != 1) {
        printf("Smth went wrong\n");
        return 1;
    }

    struct point_t* points = malloc(sizeof(struct point_t) * points_quantity);
    for (int cur_point_index = 0; cur_point_index < points_quantity; cur_point_index++) {
        scan_res = scanf("%d %d", &((points+cur_point_index)->x), &((points+cur_point_index)->y));
        if (scan_res != 2) {
            printf("Smth went wrong\n");
            return 2;
        }
    }

    printf("Points from array:\n");
    for (int cur_point_index = 0; cur_point_index < points_quantity; cur_point_index++) {
        printf("x=%d, y=%d\n", (points+cur_point_index)->x, (*(points+cur_point_index)).y);
    }

    // записываем в файл
    char* filename = malloc(31);
    printf("Enter file name:");
    scanf("%30s", filename);
    FILE* f = fopen(filename, "wb");
    if (f == NULL) {
        printf("Smth went wrong\n");
        return 4;
    }
    int elements_written = fwrite(points, sizeof(struct point_t), points_quantity, f);
    fclose(f);

    if (elements_written != points_quantity) {
        printf("Smth went wrong\n");
        return 5;
    }

    free(points);

    // читаем из файла (подходит только, если мы знаем, сколько элементов надо прочитать)
    struct point_t* p2 = malloc(sizeof(struct point_t) * points_quantity);
    FILE* f2 = fopen(filename, "rb");
    if (f2 == NULL) {
        printf("Smth went wrong\n");
        return 6;
    }
    int elements_read = fread(p2, sizeof(struct point_t), points_quantity, f2);
    fclose(f2);
    if (elements_read != points_quantity) {
        printf("Smth went wrong\n");
        return 7;
    }

    printf("Points from file:\n");
    for (int cur_point_index = 0; cur_point_index < points_quantity; cur_point_index++) {
        printf("x=%d, y=%d\n", (p2+cur_point_index)->x, (*(p2+cur_point_index)).y);
    }

    free(p2);

    return 0;
}
