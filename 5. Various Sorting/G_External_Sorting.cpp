#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// sort
void insertionSort(vector<int>& A) {
    int n = A.size();
    for (int i = 1; i < n; i++) {
        int CurrentElement = A[i];
        int j = i - 1;
        while ((j >= 0) && (A[j] > CurrentElement)) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = CurrentElement;
    }
}
void external(vector<int>& A) {
    int n = A.size();
    int chunkSize = 100;
    vector<int> sorted_data;

    for (int i = 0; i < n; i += chunkSize) {
        vector<int> buffer;
        for (int j = i; j < i + chunkSize && j < n; ++j) {
            buffer.push_back(A[j]);
        }

        insertionSort(A);

        sorted_data.insert(sorted_data.end(), buffer.begin(), buffer.end());
    }
    sort(sorted_data.begin(), sorted_data.end());
}

// read
vector<int> read(const string& fileName) {
    ifstream file(fileName);

    vector<int> array;
    int num;
    while (file >> num) {
        array.push_back(num);
    }

    file.close();

    return array;
}

// write
void write(const string& fileName, const vector<int>& array) {
    ofstream file(fileName);

    for (const int& num : array) {
        file << num << endl;
    }

    file.close();
}

// main
int main() {
    const string inputFileName = "input.txt";
    const string outputFileName = "external_output.txt";

    // read
    vector<int> array = read(inputFileName);

    // sort
    external(array);

    // write
    write(outputFileName, array);

    cout << "--- 완료 ---" << endl;
    cout << outputFileName << endl;

    return 0;
}
