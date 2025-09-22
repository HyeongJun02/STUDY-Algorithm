#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
    const string outputFileName = "insertion_output.txt";

    // read
    vector<int> array = read(inputFileName);

    // sort
    insertionSort(array);

    // write
    write(outputFileName, array);

    cout << "--- 완료 ---" << endl;
    cout << outputFileName << endl;

    return 0;
}
