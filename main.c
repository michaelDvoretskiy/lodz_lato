#include <stdio.h>
#include <stdlib.h>

struct point_t {
    char name;
    int x;
    int y;
};

// структура в структуре (именно структура, а не ссылка на нее)
struct segment_t {
    struct point_t start;
    struct point_t end;
};

void read_eol() {
    char ch;
    scanf("%c", &ch);
    while (ch != '\n') {
        scanf("%c", &ch);
    }
}

int read_point(struct point_t* p) {
    // в функцию scanf передаем ссылку на значение, которое находится в структуре
    // к самой структуре тоже ображаемся через указатель "p", например &(p->name)
    int scan_res = scanf("%c %d %d", &(p->name), &(p->x), &(p->y));
    if (scan_res != 3) {
        printf("Wrong coordinates\n");
        return 1;
    }
    return 0;
}

int read_segment(struct segment_t* s) {
    printf("Give the coordinates for point 1:\n");
    // первую точку читаем используя уже созданную функцию для чтения точки
    // "s" - указатель на отрезок, "s->start" - первая точка отрезка (структура)
    // &(s->start) - ссылка на структуру, где хранится первая ночка отрезка
    // т.к. функция read_point в  качестве параметра ждет именно указатель на точку
    int point_read_res = read_point(&(s->start));
    if (point_read_res == 1) {
        return 1;
    }

    // не могу объъяснить почему, но если не добавить эту очиистку консоли, то вторую точку читает неправильно
    read_eol();


    printf("Give the coordinates for point 2:\n");
    // вторую точку читаем прямо в поля точки конца отрезка
    // "s" - указатель на отрезок, "s->end" - структура, точка конца отрезка,
    // "(s->end).x" - поле х структуры точка, координата х конца отрезка
    // &((s->end).x) - ссылка поле структуры точка (на значение координаты х конца отрезка)
    // куда мы чиллаем значение с консоли
    int scan_res = scanf("%c %d %d", &((s->end).name), &((s->end).x), &((s->end).y));
    if (scan_res != 3) {
        printf("Wrong coordinates\n");
        return 1;
    }

    read_eol();

    return 0;
}

void show_point(struct point_t* p) {
    printf("Point %c: x=%d y=%d\n", p->name, p->x, p->y);
}

void show_segment(struct segment_t* s) {
    // s - указатель на отрезок
    // s->start - структура-точка начала отрезка
    // (s->start).name - поле name структуры точка, иимя точки начала отрезка
    printf("Segment %c%c\n", (s->start).name, (s->end).name);
    show_point(&(s->start));

    // демонстрируем 2 вида обращения к полю,
    // через структуру - (s->end).name
    // и через ссылку на структуру (&(s->end))->y
    // s - указатель на отрезок, s->end - конец отрезка, структура точка
    // (s->end).name - поле name структуры точка
    // 2-й подход &(s->end) - ссылка на структуру точка, ссылка на точку-конец отрезка
    // (&(s->end))->x - обращаемся к полю х через ссылку
    printf("Point %c: x=%d y=%d\n", (s->end).name, (&(s->end))->x, (&(s->end))->y);
}

void set_point_values(struct point_t* p, int x, int y) {
    p->x = x;
    p->y = y;
}

int main() {
    struct segment_t segm;
    int segment_read_res = read_segment(&segm);
    if (segment_read_res == 1) {
        return 1;
    }
    show_segment(&segm);
    segm.start.x = 100;
    show_segment(&segm);
    set_point_values(&(segm.end), 22, 23);
    show_segment(&segm);

    struct segment_t* segm2 = malloc(sizeof(struct segment_t));
    // передаем segm2 в функцию без &, т.к. segm2 уже указатель
    segment_read_res = read_segment(segm2);
    if (segment_read_res == 1) {
        return 1;
    }
    show_segment(segm2);
    return 0;
}
