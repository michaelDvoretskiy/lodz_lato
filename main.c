#include <stdio.h>
#include <stdlib.h>

struct date_t {
    int day;
    int month;
    int year;
};

int read_date_parts(int* day, int* month, int* year) {
    printf("enter date in DD-MM-YYYY format:");
    int scan_res = scanf("%d-%d-%d", day, month, year);
    if (scan_res != 3) {
        printf("wrong input data format");
        return 1;
    }

    return 0;
}

struct date_t* create_date(int day, int month, int year) {
    struct date_t* d = malloc(sizeof(struct date_t));
    if (d == NULL) {
        return NULL;
    }
    d->day = day;
    d->month = month;
    d->year = year;

    return d;
}

int show_date(struct date_t* d) {
    printf("%02d-%02d-%04d\n", d->day, d->month, d->year);
}

int validate_date(struct date_t* d) {
    if (d == NULL) {
        return 1;
    }
    if (d->year < 0 || d->year > 9999) {
        return 1;
    }
    if (d->month <= 0 || d->month > 12) {
        return 1;
    }

    int max_day_number = 31;
    if (d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11) {
        max_day_number = 30;
    }
    if (d->month == 2) {
        max_day_number = 28;
        if (d->year % 4 == 0 && d->year % 100 != 0) {
            max_day_number = 29;
        }
    }
    if (d->day <= 0 || d->day > max_day_number) {
        return 1;
    }

    return 0;
}

int main() {
    int day;
    int month;
    int year;
    int read_res = read_date_parts(&day, &month, &year);
    if (read_res == 1) {
        return 1;
    }
    struct date_t* d = create_date(day, month, year);
    if (validate_date(d) == 1) {
        printf("The date is invalid\n");
        return 2;
    }
    show_date(d);
    free(d);
    return 0;
}
