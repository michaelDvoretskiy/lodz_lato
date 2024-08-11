#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

struct image_t* create_image(int height, int width) {
    struct image_t* image = malloc(sizeof(struct image_t));
    if (image == NULL) {
        return NULL;
    }

    image->height = height;
    image->width = width;

    image->pixels = malloc(sizeof(int*) * height);
    if (image->pixels == NULL) {
        free(image->pixels);
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        *(image->pixels + i) = malloc(sizeof(int) * width);
        if (*(image->pixels + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(image->pixels + j));
            }
            free(image->pixels);
            free(image);
            return NULL;
        }
    }

    return image;
}

void show_image(struct image_t* image) {
    if (image == NULL || image->pixels == NULL) {
        return;
    }
    for (int i = 0; i < image->height; i++) {
        if (*(image->pixels + i) == NULL) {
            return;
        }
    }
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            printf("%c", *(*(image->pixels + i) + j) == 1 ? 'X' : ' ');
        }
        printf("\n");
    }
    printf("===================\n");
}

void destroy_image(struct image_t* image) {
    if (image == NULL || image->pixels == NULL) {
        return;
    }
    for (int i = 0; i < image->height; i++) {
        free(*(image->pixels + i));
    }
    free(image->pixels);
    free(image);
}

struct image_t* read_image_from_file(const char *filename, int *err_code) {
    if (!filename) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        if (err_code != NULL) {
            *err_code = 2;
        }
        return NULL;
    }

    int height, width;
    if (fscanf(file, "%d %d", &width, &height) != 2) {
        fclose(file);
        if (err_code != NULL) {
            *err_code = 3;
        }
        return NULL;
    }

    if (height <= 0 || width <= 0) {
        fclose(file);
        if (err_code != NULL) {
            *err_code = 3;
        }
        return NULL;
    }
    struct image_t *image = create_image(height, width);
    if (!image) {
        fclose(file);
        if (err_code != NULL) {
            *err_code = 4;
        }
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned short pixel;
            if (fscanf(file, "%hu", &pixel) != 1) {
                fclose(file);
                destroy_image(image);
                if (err_code != NULL) {
                    *err_code = 3;
                }
                return NULL;
            }
            *(*(image->pixels + i) + j) = pixel;
        }
    }

    fclose(file);
    if (err_code != NULL) {
        *err_code = 0;
    }
    return image;
}

int save_image_to_file(const struct image_t *image, const char *filename) {
    if (!image || image->height <= 0 || image->width <= 0 || !image->pixels || !filename) {
        return 1;
    }

    FILE *file = fopen(filename, "w");
    if (!file) {
        return 2;
    }

    fprintf(file, "%d %d\n", image->height, image->width);
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            fprintf(file, "%d ", *(*(image->pixels + i) + j));
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

int draw_image_on_image(struct image_t* origin_image, struct image_t* inserted_image, int start_width, int start_height) {
    if (!origin_image || !inserted_image) {
        return 1;
    }
    if (start_width < 0 || start_height < 0) {
        return 1;
    }

    if (start_width + inserted_image->width > origin_image->width || start_height + inserted_image->height > origin_image->height) {
        return 1;
    }

    for (int i = 0; i < inserted_image->height; ++i) {
        for (int j = 0; j < inserted_image->width; ++j) {
            *(*(origin_image->pixels + start_height + i) + start_width + j) = *(*(inserted_image->pixels + i) + j);
        }
    }

    return 0;
}
