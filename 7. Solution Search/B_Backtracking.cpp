#include <iostream>
#include <vector>
#include <limits.h>

#define N 5

using namespace std;

int graph[N][N] = {
    {0, 2, 7, 3, 10},
    {2, 0, 3, 5, 4},
    {7, 3, 0, 6, 1},
    {3, 5, 6, 0, 9},
    {10, 4, 1, 9, 0}
};

vector<int> result;
int minimum = INT_MAX;

int calculateDistance(const vector<int>& tour) {
    int distance = 0;
    for (size_t i = 0; i < tour.size() - 1; i++) {
        distance += graph[tour[i]][tour[i + 1]];
    }
    distance += graph[tour.back()][tour[0]];
    return distance;
}

void backtrackTSP(vector<int>& tour, vector<bool>& visited) {
    if (tour.size() == N) {
        int distance = calculateDistance(tour);
        if (distance < minimum) {
            minimum = distance;
            result = tour;
        }
        return;
    }

    for (int v = 0; v < N; v++) {
        if (!visited[v]) {
            visited[v] = true;
            tour.push_back(v);

            // 가지치기
            if (calculateDistance(tour) < minimum) {
                backtrackTSP(tour, visited);
            }

            tour.pop_back();
            visited[v] = false;
        }
    }
}

int main() {
    vector<int> tour;
    vector<bool> visited(N); // visited

    tour.push_back(0); // 시작점 A
    visited[0] = true;

    backtrackTSP(tour, visited);

    cout << "[";
    for (int city : result) {
        cout << char('A' + city) << ",";
    }
    cout << "A";
    cout << "], ";

    cout << "거리 = " << minimum << endl;

    return 0;
}
