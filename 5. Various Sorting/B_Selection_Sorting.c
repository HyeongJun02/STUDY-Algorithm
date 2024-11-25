#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 1000

// sort
void selectionSort(int *A, int size) {
    int min;
    for (int i = 0; i < size - 1; i++) {
        min = i;
        for (int j = i + 1; j < size - 1; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        int tmp = A[i];
        A[i] = A[min];
        A[min] = tmp;
    }
}

// read
int *read(const char *fileName, int *size) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        perror("READ FAIL");
        exit(EXIT_FAILURE);
    }

    int *array = (int *)malloc(MAX_NUMBERS * sizeof(int));

    int num;
    int index = 0;
    while (fscanf(file, "%d", &num) == 1) {
        array[index++] = num;
    }
    *size = index;
    fclose(file);
    return array;
}

// write
void write(const char *fileName, int *array, int size) {
    FILE *file = fopen(fileName, "w");
    if (!file) {
        perror("WRITE FAIL");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", array[i]);
    }
    fclose(file);
}

// main
int main() {
    const char *fin = "input.txt";
    const char *fout = "selection_output.txt";

    int *array;
    int size;

    // read
    array = read(fin, &size);

    // sort
    selectionSort(array, size);

    // write
    write(fout, array, size);

    printf("--- end ---\n");
    printf("%s\n", fout);

    free(array);

    return 0;
}
