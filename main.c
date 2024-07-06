#include <stdio.h>

int main() {
    FILE* outFileOdd = fopen("out-odd.txt", "w");
    FILE* outFileEven = fopen("out-even.txt", "w");
    if (outFileOdd == NULL || outFileEven == NULL) {
        printf("File open error");
        if (outFileOdd != NULL) {
            fclose(outFileOdd);
        }
        if (outFileEven != NULL) {
            fclose(outFileEven);
        }
        return 1;
    }
    int values[] = {1, 5, 6, 8, 2, 13};
    int arrSize = 6;
    for (int i = 0; i < arrSize; i++) {
        if (values[i] % 2 == 0) {
            fprintf(outFileEven, "%d\n", *(values+i));
        } else {
            fprintf(outFileOdd, "%d\n", *(values+i));
        }
    }

    fclose(outFileEven);
    fclose(outFileOdd);

    return 0;
}
