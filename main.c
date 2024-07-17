#include <stdio.h>
#include <stdlib.h>

struct point_t {
    char name;
    int x;
    int y;
};

// указатель на структуру в структуре
struct segment_t {
    struct point_t* start;
    struct point_t* end;
};

void read_eol() {
    char ch;
    scanf("%c", &ch);
    while (ch != '\n') {
        scanf("%c", &ch);
    }
}

void destroy_segment(struct segment_t* s) {
    if (s == NULL) {
        return;
    }
    if (s->start != NULL) {
        free(s->start);
        s->start = NULL;
    }
    if (s->end != NULL) {
        free(s->end);
        s->end = NULL;
    }
    free(s);
}

struct segment_t* create_segment() {
    struct segment_t* s = malloc(sizeof(struct segment_t));
    if (s == NULL) {
        return NULL;
    }
    // дальше мы будем проверять их на NULL, чтобы понять, выделялась ли память
    // не всегда если мы еще не вызывали malloc там будут NULL-ы
    // поэтому записываем их туда на всякий случай
    s->start = NULL;
    s->end = NULL;

    s->start = malloc(sizeof(struct point_t));
    if (s->start == NULL) {
        destroy_segment(s);
        return NULL;
    }

    s->end = malloc(sizeof(struct point_t));
    if (s->end == NULL) {
        destroy_segment(s);
        return NULL;
    }

    return s;
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
    // "s" - указатель на отрезок, "s->start" - указатель на первую точку отрезка (на структуру)
    int point_read_res = read_point(s->start);
    if (point_read_res == 1) {
        return 1;
    }

    // не могу объяснить почему, но если не добавить эту очиистку консоли, то вторую точку читает неправильно
    read_eol();

    printf("Give the coordinates for point 2:\n");
    // вторую точку читаем прямо в поля точки конца отрезка
    // "s" - указатель на отрезок, "s->end" - учазатель на структуру, точку конца отрезка,
    // "s->end->x" - поле х структуры точка, координата х конца отрезка
    // &(s->end->x) - ссылка на поле структуры точка (на значение координаты х конца отрезка)
    // куда мы читаем значение с консоли
    int scan_res = scanf("%c %d %d", &(s->end->name), &(s->end->x), &(s->end->y));
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
    // s->start - указатель на структуру-точку начала отрезка
    // (s->start->name - поле name структуры точка, имя точки начала отрезка
    printf("Segment %c%c\n", s->start->name, s->end->name);
    show_point(s->start);

    // s - указатель на отрезок, s->end - указатель на конец отрезка, указатель на структуру точка
    // s->end->name - поле name структуры точка
    printf("Point %c: x=%d y=%d\n", s->end->name, s->end->x, s->end->y);
}

void set_point_values(struct point_t* p, int x, int y) {
    p->x = x;
    p->y = y;
}

int main() {
    // начало и конец отрезка - это указатели на структуру, а не сама структура
    // под саму структуру точка нужно еще выделить память
    // т.е. нам надо выделить память под отрезок и под 2 точки, в процессу может что то пойти не так
    // поэтому мы сделали функцию create_segment, которая выполнит эту работу
    struct segment_t* segm = create_segment();
    if (segm == NULL) {
        printf("error while creating a segment\n");
        return 1;
    }

    int segment_read_res = read_segment(segm);
    if (segment_read_res == 1) {
        return 1;
    }
    // segm - это указатель, поэтому теперь, когда мы вызываем show_segment, нам не нужен &
    show_segment(segm);
    // segm - это указатель, в котором точки начала и конца тоже указатели
    // поэтому все ображения через ->, а не через .
    segm->start->x = 100;
    show_segment(segm);
    set_point_values(segm->end, 22, 23);
    show_segment(segm);


    // создаем второй отрезок
    struct segment_t* segm2 = create_segment();
    segment_read_res = read_segment(segm2);
    if (segment_read_res == 1) {
        return 1;
    }
    show_segment(segm2);

    // присваеваем концу второго отрезка точку-конец первого отрезка
    segm2->end = segm->end;
    // напоминаю, что в структуре отрезок точки начала и конца - это не структуры точка
    // а указатели на структуру точка
    // поэтому теперь в двух отрезках точки их концов - это вказатели на одну и ту же структуру (область памяти)

    // меняем значения полей структуры точка, на которую указывает поле end второго отрезка
    set_point_values(segm2->end, -10, -20);
    // убеждаемся в том, что значения поменялись и для первого и для второго отрезков
    // т.к. их концы указывают на одну и ту же структуру точка
    show_segment(segm);
    show_segment(segm2);

    destroy_segment(segm);
    destroy_segment(segm2);

    // еще один интересный факт, когда мы вызывали функцию create_segment
    // для двух сегментов, то выделялась память как под сегмент, так и под точки начала-конца сегмента (отрезка)
    // потом  мы сделали "segm2->end = segm->end;", после чего концы отрезка стали указывать
    // на одну структуру точка (ту, что была выделена изначально для 1-го сермента.
    // А та, что была выделена для второго, остатась в памяти, на нее ничего не указывает и она осталась неочишенной
    // Это скорее всего будет утечка памяти
    return 0;
}
