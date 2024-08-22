#include <stdio.h>
#include "person.h"

int main() {
    int persons_count = 5;
    struct person_t* person_list = create_persons();

    display_persons(person_list, persons_count);

    int sort_type;
    printf("How to sort persons ? (0 - by name, 1 - by age):");
    if (scanf("%d", &sort_type) != 1) {
        return 1;
    }
    if (sort_type != 0 && sort_type != 1) {
        return 1;
    }

    void (*sort_fun)(struct person_t*, int) = get_sorter(sort_type);
    sort_fun(person_list, persons_count);
    display_persons(person_list, persons_count);

    destroy_persons(person_list, persons_count);

    return 0;
}
