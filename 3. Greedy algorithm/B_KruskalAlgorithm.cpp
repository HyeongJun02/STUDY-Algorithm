#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

// 간선 struct
struct Edge {
    // u: 시작점
    // v: 끝점
    // weight: 가중치
    int u, v, weight;
};

// 정렬 - 비교 함수 (가중치 작은 순)
bool compareEdge(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int main() {
    // 그래프의 간선들 초기화
    // a:0, b:1, c:2, d:3, e:4로 정의
    vector<Edge> edges = {
        {1, 2, 1},  // b-c
        {2, 5, 1},  // c-f
        {1, 5, 2},  // b-f
        {0, 3, 2},  // a-d
        {3, 4, 3},  // d-e
        {0, 4, 4},  // a-e
        {1, 3, 4},  // b-d
        {3, 5, 7},  // d-f
        {0, 1, 8},  // a-b
        {4, 5, 9}   // e-f
    };

    int num_vertices = 6; // 정점의 수 (a, b, c, d, e, f)
    vector<int> component(num_vertices); // 각 정점의 컴포넌트 번호
    for (int i = 0; i < num_vertices; i++) {
        component[i] = i;
    }
    vector<Edge> result; // 최소 스패닝 트리에 포함된 간선들

    // 가중치 작은 순 정렬
    sort(edges.begin(), edges.end(), compareEdge);

    // 시간 측정 start
    auto start = high_resolution_clock::now();

    for (const auto& edge : edges) {
        // 두 정점이 서로 다른 컴포넌트에 속해 있는 경우 추가
        if (component[edge.u] != component[edge.v]) {
            result.push_back(edge);
            int old_component = component[edge.v];
            int new_component = component[edge.u];

            // 두 컴포넌트를 병합
            for (int i = 0; i < num_vertices; i++) {
                if (component[i] == old_component) {
                    component[i] = new_component;
                }
            }
        }
        // 최소 스패닝 트리의 간선 수가 정점 수 - 1이면 종료
        if (result.size() == num_vertices - 1) {
            break;
        }
    }

    // 실행 시간 측정 end
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    for (const auto& edge : result) {
        cout << "(" << edge.u << ", " << edge.v << ", " << edge.weight << ")\n";
    }

    cout << "running time: " << duration.count() / 1000000.0 << " milliseconds (너무 짧아서 단위를 ms로 설정)" << endl;

    return 0;
}
