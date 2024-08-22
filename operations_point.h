#ifndef CODE_OPERATIONS_POINT_H
#define CODE_OPERATIONS_POINT_H

struct point_t {
    int x;
    int y;
};

void* add_point(const void* p1, const void*p2);
void* sub_point(const void* p1, const void* p2);
int read_input_point(void** p1, void** p2);
void show_result_point(void* res);

#endif //CODE_OPERATIONS_POINT_H
