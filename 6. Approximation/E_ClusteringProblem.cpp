#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
    int cluster;

    Point(double x, double y) : x(x), y(y), cluster(-1) {}
};

double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void print(const vector<Point>& points, const vector<Point>& centers, int k) {
    for (int j = 0; j < k; ++j) {
        cout << "Cluster" << j + 1 << endl;
        cout << "Center: (" << centers[j].x << ", " << centers[j].y << ")\n";
        cout << "Points: ";
        for (const auto& point : points) {
            if (point.cluster == j) {
                cout << "(" << point.x << ", " << point.y << ") ";
            }
        }
        cout << "\n\n";
    }
}

void clustering(vector<Point>& points, int k) {
    vector<Point> centers;

    // 1
    centers.push_back(points[0]);

    // 2
    for (int j = 1; j < k; ++j) {
        vector<double> distances(points.size(), numeric_limits<double>::max());

        for (size_t i = 0; i < points.size(); ++i) {
            if (points[i].cluster != -1) continue;

            for (const auto& center : centers) {
                double dist = distance(points[i], center);
                distances[i] = min(distances[i], dist);
            }
        }

        int newCenterIndex = max_element(distances.begin(), distances.end()) - distances.begin();
        centers.push_back(points[newCenterIndex]);
        points[newCenterIndex].cluster = j;
    }

    // 3
    for (auto& point : points) {
        double minDistance = numeric_limits<double>::max();
        int closestCenter = -1;

        for (size_t j = 0; j < centers.size(); ++j) {
            double dist = distance(point, centers[j]);
            if (dist < minDistance) {
                minDistance = dist;
                closestCenter = j;
            }
        }
        point.cluster = closestCenter;
    }

    bool changed = true;
    while (changed) {
        changed = false;

        vector<Point> newCenters(k, Point(0, 0));
        vector<int> clusterCounts(k, 0);

        for (const auto& point : points) {
            newCenters[point.cluster].x += point.x;
            newCenters[point.cluster].y += point.y;
            clusterCounts[point.cluster]++;
        }

        for (int j = 0; j < k; ++j) {
            if (clusterCounts[j] > 0) {
                newCenters[j].x /= clusterCounts[j];
                newCenters[j].y /= clusterCounts[j];
            }
        }

        for (int j = 0; j < k; ++j) {
            if (distance(centers[j], newCenters[j]) > 1e-6) {
                changed = true;
            }
        }
        centers = newCenters;

        for (auto& point : points) {
            double minDistance = numeric_limits<double>::max();
            int closestCenter = -1;

            for (size_t j = 0; j < centers.size(); ++j) {
                double dist = distance(point, centers[j]);
                if (dist < minDistance) {
                    minDistance = dist;
                    closestCenter = j;
                }
            }
            point.cluster = closestCenter;
        }
    }

    print(points, centers, k);
}

int main() {
    ifstream inputFile("clustering_input.txt");

    set<pair<double, double>> uniquePoints;
    vector<Point> points;

    double x, y;
    while (inputFile >> x >> y) {
        if (uniquePoints.insert({x, y}).second) {
            points.emplace_back(x, y);
        }
    }
    inputFile.close();

    int k = 8;
    clustering(points, k);

    return 0;
}
