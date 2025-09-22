#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define CROSSOVER_RATIO 1.0
#define MUTATION_RATIO 0.01

#define POINT_SIZE 8
#define POP_SIZE 8

#define MAX_GENERATIONS 1000

typedef struct {
    char name;
    double x, y;
} Point;

typedef struct {
    int path[POINT_SIZE];
    double distance;
} Individual;

Point points[POINT_SIZE] = {
    {'A', 0, 3}, {'B', 7, 5}, {'C', 6, 0}, {'D', 4, 3},
    {'E', 1, 0}, {'F', 5, 3}, {'G', 2, 2}, {'H', 4, 1}
};

double calculateDistance(int path[]) {
    double total = 0.0;
    for (int i = 0; i < POINT_SIZE - 1; i++) {
        double dx = points[path[i]].x - points[path[i + 1]].x;
        double dy = points[path[i]].y - points[path[i + 1]].y;
        total += sqrt(dx * dx + dy * dy);
    }
    double dx = points[path[POINT_SIZE - 1]].x - points[path[0]].x;
    double dy = points[path[POINT_SIZE - 1]].y - points[path[0]].y;
    total += sqrt(dx * dx + dy * dy);
    return total;
}

void initializePopulation(Individual population[]) {
    for (int i = 0; i < POP_SIZE; i++) {
        for (int j = 1; j < POINT_SIZE; j++) {
            population[i].path[j - 1] = j;
        }
        for (int j = POINT_SIZE - 2; j > 0; j--) {
            int k = rand() % (j + 1);
            int temp = population[i].path[j];
            population[i].path[j] = population[i].path[k];
            population[i].path[k] = temp;
        }
        for (int j = POINT_SIZE - 1; j > 0; j--) {
            population[i].path[j] = population[i].path[j - 1];
        }
        population[i].path[0] = 0;
        population[i].distance = calculateDistance(population[i].path);
    }
}

void crossover(int parent1[], int parent2[], int child[]) {
    int start = rand() % (POINT_SIZE - 1) + 1;
    int end = rand() % (POINT_SIZE - 1) + 1;
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }
    int visited[POINT_SIZE] = {0};
    for (int i = start; i <= end; i++) {
        child[i] = parent1[i];
        visited[child[i]] = 1;
    }
    int current = 1;
    for (int i = 1; i < POINT_SIZE; i++) {
        if (i >= start && i <= end) continue;
        while (visited[parent2[current]]) {
            current++;
        }
        child[i] = parent2[current];
        visited[child[i]] = 1;
    }
    child[0] = 0;
}

void mutate(int path[]) {
    if ((double)rand() / RAND_MAX < MUTATION_RATIO) {
        int i = rand() % (POINT_SIZE - 1) + 1;
        int j = rand() % (POINT_SIZE - 1) + 1;
        int temp = path[i];
        path[i] = path[j];
        path[j] = temp;
    }
}

void selectParents(Individual population[], Individual *parent1, Individual *parent2) {
    int idx1 = rand() % POP_SIZE;
    int idx2 = rand() % POP_SIZE;
    while (idx2 == idx1) {
        idx2 = rand() % POP_SIZE;
    }
    *parent1 = population[idx1];
    *parent2 = population[idx2];
}

void geneticAlgorithm() {
    Individual population[POP_SIZE];
    Individual newPopulation[POP_SIZE];
    initializePopulation(population);

    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        for (int i = 0; i < POP_SIZE; i++) {
            Individual parent1, parent2, child;
            selectParents(population, &parent1, &parent2);
            crossover(parent1.path, parent2.path, child.path);
            mutate(child.path);
            child.distance = calculateDistance(child.path);
            newPopulation[i] = child;
        }
        for (int i = 0; i < POP_SIZE; i++) {
            population[i] = newPopulation[i];
        }
    }

    Individual best = population[0];
    for (int i = 1; i < POP_SIZE; i++) {
        if (population[i].distance < best.distance) {
            best = population[i];
        }
    }

    printf("이동 순서: ");
    for (int i = 0; i < POINT_SIZE; i++) {
        printf("%c ", points[best.path[i]].name);
    }
    printf("\n이동 거리: %.2f\n", best.distance);
}

int main() {
    srand(time(NULL));
    geneticAlgorithm();
    return 0;
}
