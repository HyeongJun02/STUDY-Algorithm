#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <set>

using namespace std;

struct Point {
    char name;
    double x, y;
};

double getDistance(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

struct Edge {
    int u, v;
    double weight;
    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

// MST
vector<Edge> mst(int n, const vector<vector<double>> &dist) {
    vector<bool> visited(n, false);
    vector<Edge> mstEdges;
    vector<double> minDist(n, INT_MAX);
    vector<int> parent(n, -1);

    minDist[0] = 0;

    for (int i = 0; i < n; i++) {
        double min = INT_MAX;
        int u = -1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && minDist[v] < min) {
                min = minDist[v];
                u = v;
            }
        }

        visited[u] = true;

        if (parent[u] != -1) {
            mstEdges.push_back({parent[u], u, dist[parent[u]][u]});
        }

        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[u][v] < minDist[v]) {
                minDist[v] = dist[u][v];
                parent[v] = u;
            }
        }
    }
    return mstEdges;
}

// DFS
void dfs(int u, const vector<vector<int>> &tree, vector<bool> &visited, vector<int> &order) {
    visited[u] = true;
    order.push_back(u);

    for (int v : tree[u]) {
        if (!visited[v]) {
            dfs(v, tree, visited, order);
        }
    }
}

int main() {
    vector<Point> points = {
        {'A', 0, 3}, {'B', 7, 5}, {'C', 6, 0}, {'D', 4, 3},
        {'E', 1, 0}, {'F', 5, 3}, {'H', 4, 1}, {'G', 2, 2}
    };

    int n = points.size();
    vector<vector<double>> dist(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = getDistance(points[i], points[j]);
        }
    }

    // MST
    vector<Edge> mstEdges = mst(n, dist);

    // MST Tree
    vector<vector<int>> tree(n);
    for (const Edge &edge : mstEdges) {
        tree[edge.u].push_back(edge.v);
        tree[edge.v].push_back(edge.u);
    }

    vector<int> order;
    vector<bool> visited(n, false);
    dfs(0, tree, visited, order);

    vector<int> result;
    set<int> visitedNodes;
    for (int city : order) {
        if (visitedNodes.find(city) == visitedNodes.end()) {
            result.push_back(city);
            visitedNodes.insert(city);
        }
    }
    result.push_back(0);

    cout << "이동 순서: ";
    double distance = 0;
    for (size_t i = 0; i < result.size(); i++) {
        cout << points[result[i]].name;
        if (i < result.size() - 1) {
            cout << " -> ";
            distance += dist[result[i]][result[i + 1]];
        }
    }
    cout << endl;

    cout << "이동 거리: " << distance << endl;

    return 0;
}
