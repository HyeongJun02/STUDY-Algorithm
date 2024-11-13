#include <stdio.h>
#include <limits.h>
#include <time.h>

#define CITY_COUNT 10

const char* city_names[CITY_COUNT] = { "서울", "천안", "원주", "대전", "논산", "광주", "부산", "대구", "강릉", "포항" };

void print(int a[CITY_COUNT][CITY_COUNT]) {
    printf("      ");
    for (int i = 0; i < CITY_COUNT; i++) {
        printf("%6s  ", city_names[i]);
    }
    printf("\n");
    for (int i = 0; i < CITY_COUNT; i++) {
        printf("%6s", city_names[i]);
        for (int j = 0; j < CITY_COUNT; j++) {
            if (j >= i) {
                if (a[i][j] == INT_MAX) {
                    printf("%6s", "INF");
                }
                else {
                    printf("%6d", a[i][j]);
                }
            } else {
                printf("%6s", "");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void floyd_warshall(int graph[CITY_COUNT][CITY_COUNT], int D[CITY_COUNT][CITY_COUNT]) {
    for (int i = 0; i < CITY_COUNT; i++) {
        for (int j = 0; j < CITY_COUNT; j++) {
            D[i][j] = graph[i][j];
        }
    }

    // O(n^3) gogo
    for (int k = 0; k < CITY_COUNT; k++) {
        for (int i = 0; i < CITY_COUNT; i++) {
            for (int j = 0; j < CITY_COUNT; j++) {
                if (D[i][k] != INT_MAX && D[k][j] != INT_MAX
                    && D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}

int main() {
    clock_t start_time, end_time;

    int input[CITY_COUNT][CITY_COUNT] = {
        {0, 12, 15, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, // 서울
        {12, 0, INT_MAX, 10, 4, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},       // 천안
        {15, INT_MAX, 0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 7, 21, INT_MAX},       // 원주
        {INT_MAX, 10, INT_MAX, 0, 3, INT_MAX, INT_MAX, 10, INT_MAX, INT_MAX},       // 대전
        {INT_MAX, 4, INT_MAX, 3, 0, 13, INT_MAX, INT_MAX, INT_MAX, INT_MAX},        // 논산
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 13, 0, 15, INT_MAX, INT_MAX, INT_MAX}, // 광주
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 15, 0, 9, INT_MAX, 5},        // 부산
        {INT_MAX, INT_MAX, 7, 10, INT_MAX, INT_MAX, 9, 0, INT_MAX, 19},             // 대구
        {INT_MAX, INT_MAX, 21, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 25}, // 강릉
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 5, 19, 25, 0}        // 포항
    };

    // no directed graph!!!
    for (int i = 0; i < CITY_COUNT; i++) {
        for (int j = 0; j < CITY_COUNT; j++) {
            if (input[i][j] != input[j][i]) {
                if (input[i][j] > input[j][i]){
                    input[j][i] = input[i][j];
                }
                else {
                    input[i][j] = input[j][i];
                }
            }
        }
    }

    printf("input:\n");
    print(input);

    int dist[CITY_COUNT][CITY_COUNT];

    start_time = clock();

    floyd_warshall(input, dist);

    end_time = clock();

    printf("result:\n");
    print(dist);

    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Running time: %.6f s\n", elapsed_time);

    return 0;
}
