#ifndef CODE_ARRAYS_H
#define CODE_ARRAYS_H

short* create_arr(int size);

void show_arr(short* arr, int size);

short* concat_arr(short* arr1, int size1, short* arr2, int size2);

void concat_arr2(short* arr1, int size1, short* arr2, int size2, short** new_arr, int* err_code);

void concat_arr3(short** arr1, int size1, short* arr2, int size2, int* err_code);

#endif //CODE_ARRAYS_H
