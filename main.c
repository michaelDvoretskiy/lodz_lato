#include "list.h"

int main() {

//    struct header_t header;
//
//    char *column_names[] = {"glass", "position", "made", "invent", "particular", "my"};
//    enum type_t types[] = {INT, DBL, STR, STR, DBL, STR};
//
//    FILE *f = fopen("suffix.txt", "rt");
//
//    int err_code = read_header(&header, f);

    struct list_t* list;
    if (read_file(&list, "step.txt") != 0) {
        return 1;
    }
    show_header(list->header);
    show_list(list);
//    free_list(&list);
    return 0;
}
