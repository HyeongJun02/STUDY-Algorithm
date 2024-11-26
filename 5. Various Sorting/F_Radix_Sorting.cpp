#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// sort
void radixSort_LSD(vector<int>& A) {
    int n = A.size();
}
void radixSort_MSD(vector<int>& A) {
    int n = A.size();
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
