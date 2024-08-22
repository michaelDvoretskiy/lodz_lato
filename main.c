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

    int (*compare_by)(struct person_t* p1, struct person_t* p2) = get_comparator(sort_type);
    sort_persons(person_list, persons_count, compare_by);
    display_persons(person_list, persons_count);

    destroy_persons(person_list, persons_count);

    return 0;
}
