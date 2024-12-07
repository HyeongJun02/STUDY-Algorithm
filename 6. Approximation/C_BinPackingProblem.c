#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAPACITY 10
#define NUM_ITEMS 8

void print(int bins[][NUM_ITEMS], int count[], int total) {
    for (int i = 0; i < total; i++) {
        printf("bin%d = [", i + 1);
        for (int j = 0; j < count[i]; j++) {
            printf("%d", bins[i][j]);
            if (j < count[i] - 1) printf(", ");
        }
        printf("]\n");
    }
}

// First Fit
void firstFit(int items[], int n) {
    int bins[NUM_ITEMS][NUM_ITEMS] = {0};
    int count[NUM_ITEMS] = {0};
    int use[NUM_ITEMS] = {0};
    int total = 0;

    for (int i = 0; i < n; i++) {
        bool placed = false;
        for (int j = 0; j < total; j++) {
            if (use[j] + items[i] <= CAPACITY) {
                bins[j][count[j]++] = items[i];
                use[j] += items[i];
                placed = true;
                break;
            }
        }
        if (!placed) {
            bins[total][count[total]++] = items[i];
            use[total++] = items[i];
        }
    }

    printf("Output1 (First Fit):\n");
    print(bins, count, total);
}

// Next Fit
void nextFit(int items[], int n) {
    int bins[NUM_ITEMS][NUM_ITEMS] = {0};
    int count[NUM_ITEMS] = {0};
    int use[NUM_ITEMS] = {0};
    int total = 1;

    for (int i = 0; i < n; i++) {
        if (use[total - 1] + items[i] <= CAPACITY) {
            bins[total - 1][count[total - 1]++] = items[i];
            use[total - 1] += items[i];
        } else {
            bins[total][count[total]++] = items[i];
            use[total++] = items[i];
        }
    }

    printf("Output2 (Next Fit):\n");
    print(bins, count, total);
}

// Best Fit
void bestFit(int items[], int n) {
    int bins[NUM_ITEMS][NUM_ITEMS] = {0};
    int count[NUM_ITEMS] = {0};
    int use[NUM_ITEMS] = {0};
    int total = 0;

    for (int i = 0; i < n; i++) {
        int min = CAPACITY + 1;
        int best = -1;

        for (int j = 0; j < total; j++) {
            int remain = CAPACITY - use[j];
            if (items[i] <= remain && remain < min) {
                min = remain;
                best = j;
            }
        }

        if (best != -1) {
            bins[best][count[best]++] = items[i];
            use[best] += items[i];
        } else {
            bins[total][count[total]++] = items[i];
            use[total++] = items[i];
        }
    }

    printf("Output3 (Best Fit):\n");
    print(bins, count, total);
}

// Worst Fit
void worstFit(int items[], int n) {
    int bins[NUM_ITEMS][NUM_ITEMS] = {0};
    int count[NUM_ITEMS] = {0};
    int use[NUM_ITEMS] = {0};
    int total = 0;

    for (int i = 0; i < n; i++) {
        int max = -1;
        int worst = -1;

        for (int j = 0; j < total; j++) {
            int remain = CAPACITY - use[j];
            if (items[i] <= remain && remain > max) {
                max = remain;
                worst = j;
            }
        }

        if (worst != -1) {
            bins[worst][count[worst]++] = items[i];
            use[worst] += items[i];
        } else {
            bins[total][count[total]++] = items[i];
            use[total++] = items[i];
        }
    }

    printf("Output4 (Worst Fit):\n");
    print(bins, count, total);
}

int main() {
    int items[] = {7, 5, 6, 4, 2, 3, 7, 5};
    int n = sizeof(items) / sizeof(items[0]);

    firstFit(items, n);
    nextFit(items, n);
    bestFit(items, n);
    worstFit(items, n);

    return 0;
}
