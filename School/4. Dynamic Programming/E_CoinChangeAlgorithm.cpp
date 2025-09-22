#include <iostream>
#include <limits.h>
#include <iomanip>

#define VALUE 20

int D[5] = { 10000, 16, 10, 5, 1 };
int C[VALUE + 1];

using namespace std;

void coinChange(int value) {
    C[0] = 0;
    for (int i = 1; i < value + 1; i++) {
        C[i] = INT_MAX;
    }

    for (int j = 1; j < value + 1; j++) {
        for (int i = 1; i < 5; i++) {
            if ((D[i] <= j) && (C[j - D[i]] + 1 < C[j])) {
                C[j] = C[j - D[i]] + 1;
            }
        }
    }

    cout << "j | ";
    for (int i = 0; i < VALUE + 1; i++) {
        cout << setw(2) << i << " | ";
    }
    cout << endl;
    cout << "c | ";
    for (int i = 0; i < VALUE + 1; i++) {
        cout << setw(2) << C[i] << " | ";
    }
    cout << endl;
}

int main() {
    coinChange(VALUE);
    return 0;
}
