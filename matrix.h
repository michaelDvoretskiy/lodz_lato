#ifndef CODE_MATRIX_H
#define CODE_MATRIX_H

struct image_t {
    unsigned short** pixels;
    int width;
    int height;
};

struct image_t* create_image(int height, int width);

void show_image(struct image_t* image);

void destroy_image(struct image_t* image);

struct image_t* read_image_from_file(const char *filename, int *err_code);

int save_image_to_file(const struct image_t *image, const char *filename);

int draw_image_on_image(struct image_t* origin_image, struct image_t* inserted_image, int start_width, int start_height);

#endif //CODE_MATRIX_H
