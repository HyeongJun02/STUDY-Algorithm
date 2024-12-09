#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <set>
#include <limits>
#include <algorithm>

#define CLUSTER_COUNT 8

using namespace std;

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

double distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void clustering(vector<Point>& points, int k, vector<vector<Point>>& clusters, vector<Point>& centers) {
    int n = points.size();
    centers.push_back(points[0]);

    vector<bool> isCenter(n, false);
    isCenter[0] = true;

    for (int j = 1; j < k; ++j) {
        double maxDistance = -1;
        int next = -1;

        for (int i = 0; i < n; ++i) {
            if (!isCenter[i]) {
                double minDistance = numeric_limits<double>::max();
                for (const auto& center : centers) {
                    minDistance = min(minDistance, distance(points[i], center));
                }
                if (minDistance > maxDistance) {
                    maxDistance = minDistance;
                    next = i;
                }
            }
        }
        centers.push_back(points[next]);
        isCenter[next] = true;
    }

    clusters.clear();
    clusters.resize(k);

    for (const auto& point : points) {
        double minDistance = numeric_limits<double>::max();
        int index = 0;
        for (int i = 0; i < k; ++i) {
            double dist = distance(point, centers[i]);
            if (dist < minDistance) {
                minDistance = dist;
                index = i;
            }
        }
        clusters[index].push_back(point);
    }
}

void print(const vector<vector<Point>>& clusters, const vector<Point>& centers) {
    for (size_t i = 0; i < clusters.size(); ++i) {
        cout << "Cluster " << i + 1 << endl;
        cout << "Center (" << centers[i].x << ", " << centers[i].y << ")" << endl;
        cout << "-------------------------------------------" << endl;
        for (const auto& point : clusters[i]) {
            cout << "(" << point.x << ", " << point.y << ")" << endl;
        }
        cout << "===========================================" << endl;
    }
}

int main() {
    ifstream inputFile("clustering_input.txt");
    set<pair<int, int>> inputPoints;
    int x, y;
    vector<vector<Point>> clusters;
    vector<Point> centers;

    while (inputFile >> x >> y) {
        inputPoints.insert({ x, y });
    }
    inputFile.close();

    vector<Point> points;
    for (const auto& p : inputPoints) {
        points.emplace_back(p.first, p.second);
    }

    clustering(points, CLUSTER_COUNT, clusters, centers);

    print(clusters, centers);

    return 0;
}
