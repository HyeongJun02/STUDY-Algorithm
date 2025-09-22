#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

// sort
void radixSort_LSD(vector<int>& A) {
    int n = A.size();
    vector <int>temp;
    // int div;
    for (int i = 1; i <= 1000; i *= 10) {
        // cout << "i: " << i << endl;
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k < n; k++) {
                int AC = (A.at(k) / i) % 10;
                // cout << "AC: " << AC << endl;
                if (AC == j) {
                    temp.push_back(A.at(k));
                }
            }
        }
        for (int k = 0; k < n; k++) {
            A[k] = temp[k];
            // cout << A[k] << " ";
        }
        // cout << endl << "---" << endl;
        temp.clear();
    }
}
void radixSort_MSD(vector<int>& A, int tries = 0) {
    if (tries == 0) {
        int max = *max_element(A.begin(), A.end());
        tries = 1;
        while (max / tries > 0) tries *= 10;
        tries /= 10;
    }

    if (tries == 0) return;

    vector<vector<int>> nTemp(10);
    for (int num : A) {
        int digit = (num / tries) % 10;
        nTemp[digit].push_back(num);
    }

    size_t index = 0;
    for (int i = 0; i < 10; i++) {
        if (!nTemp[i].empty()) {
            if (tries / 10 > 0) {
                radixSort_MSD(nTemp[i], tries / 10);
            }
            for (int num : nTemp[i]) {
                A[index++] = num;
            }
        }
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
    const string outputFileNameLSD = "radix_lsd_output.txt";
    const string outputFileNameMSD = "radix_msd_output.txt";

    // read
    vector<int> arrayLCD = read(inputFileName);
    vector<int> arrayMSD = read(inputFileName);

    // sort
    radixSort_LSD(arrayLCD);
    radixSort_MSD(arrayMSD);

    // write
    write(outputFileNameLSD, arrayLCD);
    write(outputFileNameMSD, arrayMSD);

    cout << "--- 완료 ---" << endl;
    cout << outputFileNameLSD << endl;
    cout << outputFileNameMSD << endl;

    return 0;
}
