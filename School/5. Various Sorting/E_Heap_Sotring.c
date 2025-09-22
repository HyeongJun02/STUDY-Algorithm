#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 1000

// sort
void downHeap(int *A, int i, int n) {
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;
    int now = i;

    if (leftChild < n && A[leftChild] > A[now]) {
        now = leftChild;
    }

    if (rightChild < n && A[rightChild] > A[now]) {
        now = rightChild;
    }

    if (now != i) {
        int tmp = A[i];
        A[i] = A[now];
        A[now] = tmp;

        downHeap(A, now, n);
    }
}

void buildHeap(int *A, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        downHeap(A, i, size);
    }
}

void heapSort(int *A, int size) {
    buildHeap(A, size);

    int n = size;

    for (int i = size - 1; i > 0; i--) {
        int tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;

        n--;

        downHeap(A, 0, n);
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
    const char *fout = "heap_output.txt";

    int *array;
    int size;

    // read
    array = read(fin, &size);

    // sort
    heapSort(array, size);

    // write
    write(fout, array, size);

    printf("--- end ---\n");
    printf("%s\n", fout);

    free(array);

    return 0;
}
