#ifndef CODE_SORT_H
#define CODE_SORT_H

struct point_t {
    int x;
    int y;
};

void sort_array(void* array, size_t elements_in_array, size_t elem_size, int (*comparator)(const void*, const void*));

int compare_int(const void* x, const void* y);
int compare_float(const void* x, const void* y);
int compare_point(const void* p1, const void* p2);

#endif //CODE_SORT_H
