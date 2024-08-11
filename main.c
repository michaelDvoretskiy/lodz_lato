#include <stdio.h>
#include "matrix.h"

int main() {
    int err;
    struct image_t* img1 = read_image_from_file("image1.txt", &err);
    if (err != 0) {
        return 1;
    }
    show_image(img1);

    struct image_t* img2 = read_image_from_file("image2.txt", &err);
    if (err != 0) {
        return 1;
    }
    show_image(img2);

    err = draw_image_on_image(img1, img2, 1, 3);
    if (err != 0) {
        return 1;
    }
    show_image(img1);

    err = save_image_to_file(img1, "image3.txt");
    if (err != 0) {
        return 1;
    }

    return 0;
}
