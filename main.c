#include "list.h"

int main() {
    struct list_t* list;
    if (read_file(&list, "quick.txt") != 0) {
        return 1;
    }
    show_list(list);
    free_list(&list);
    return 0;
}
