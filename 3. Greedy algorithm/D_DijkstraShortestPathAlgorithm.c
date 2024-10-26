#include <stdio.h>
#include <limits.h>

#define CITY_COUNT 10

const char* city_names[CITY_COUNT] = { "서울", "천안", "원주", "대전", "논산", "광주", "부산", "대구", "강릉", "포항" };

void print(int a[CITY_COUNT][CITY_COUNT]) {
    printf("      ");
    for (int i = 0; i < CITY_COUNT; i++) {
        printf("%6s", city_names[i]);
    }
    printf("\n");
    for (int i = 0; i < CITY_COUNT; i++) {
        printf("%6s", city_names[i]);
        for (int j = 0; j < CITY_COUNT; j++) {
            if (a[i][j] == INT_MAX) {
                printf("%6s", "INF");
            }
            else {
                printf("%6d", a[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void dijkstra(int graph[CITY_COUNT][CITY_COUNT], int start, int result[CITY_COUNT]) {
    int D[CITY_COUNT];
    int visited[CITY_COUNT] = {0};

    for (int i = 0; i < CITY_COUNT; i++) {
        D[i] = INT_MAX;
    }
    D[start] = 0;

    // 다익스트라 알고리즘 Start
    for (int count = 0; count < CITY_COUNT; count++) {
        int min = INT_MAX, u = -1;
        // 최소 거리 정점 선택
        for (int i = 0; i < CITY_COUNT; i++) {
            if (!visited[i] && D[i] <= min) {
                min = D[i];
                u = i;
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = 1;

        for (int v = 0; v < CITY_COUNT; v++) {
            if (!visited[v] && graph[u][v] != INT_MAX && D[u] != INT_MAX && D[u] + graph[u][v] < D[v]) {
                D[v] = D[u] + graph[u][v];
            }
        }
    }
    // 다익스트라 알고리즘 End

    for (int i = 0; i < CITY_COUNT; i++) {
        result[i] = D[i];
    }
}

int main() {
    int input[CITY_COUNT][CITY_COUNT] = {
        {0, 12, 15, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, // 서울
        {12, 0, INT_MAX, 10, 4, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},       // 천안
        {15, INT_MAX, 0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 7, 21, INT_MAX},       // 원주
        {INT_MAX, 10, INT_MAX, 0, INT_MAX, INT_MAX, INT_MAX, 10, INT_MAX, INT_MAX}, // 대전
        {INT_MAX, 4, INT_MAX, 3, 0, 13, INT_MAX, INT_MAX, INT_MAX, INT_MAX},        // 논산
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 13, 0, 15, INT_MAX, INT_MAX, INT_MAX}, // 광주
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 15, 0, 9, INT_MAX, 5},        // 부산
        {INT_MAX, INT_MAX, 7, 10, INT_MAX, INT_MAX, 9, 0, INT_MAX, 19},             // 대구
        {INT_MAX, INT_MAX, 21, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 25}, // 강릉
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 5, 19, 25, 0}        // 포항
    };

    print(input);

    int result[CITY_COUNT][CITY_COUNT];
    for (int i = 0; i < CITY_COUNT; i++) {
        for (int j = 0; j < CITY_COUNT; j++) {
            result[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < CITY_COUNT; i++) {
        dijkstra(input, i, result[i]);
    }

    printf("최단 거리 결과 (모든 도시 간 최단 거리):\n");
    print(result);

    return 0;
}
