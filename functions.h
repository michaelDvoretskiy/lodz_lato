#ifndef CODE_FUNCTIONS_H
#define CODE_FUNCTIONS_H

int add(int x, int y);
int sub(int x, int y);
void show(int x);
void show2(int x);

void make_job(int x, int y, int (*operation)(int, int), void (*display)(int));

#endif //CODE_FUNCTIONS_H
