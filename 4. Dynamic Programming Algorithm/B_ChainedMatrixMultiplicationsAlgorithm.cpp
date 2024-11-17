#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits.h>
#include <iomanip>

using namespace std;

#define MATRIX_SIZE 10

struct Matrix {
    int index; // 인덱스
    int cols; // 행
    int rows; // 열
};

vector<Matrix> matrices;

//void readFile(const string& filename) {
//    ifstream file(filename);
//    if (!file.is_open()) {
//        cerr << "파일을 열기 실패요. " << filename << endl;
//        return;
//    }
//
//    string line;
//    while (getline(file, line)) {
//        cout << line << endl; // 파일 내용을 한 줄씩 출력
//    }
//
//    file.close();
//}

void getSize(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "파일을 열기 실패요. " << filename << endl;
        return;
    }

    string line;
    int index = 1;
    int readCount = 0;

    while (readCount != MATRIX_SIZE) {
        getline(file, line);
        // 행렬 시작
        if (line.find('=') != string::npos) {
            readCount++;
            //cout << "readCount: " << readCount << endl;
            int rows = 0, cols = 0;

            while (true) {
                //cout << line << endl;
                size_t posOpen = line.find('[');                // 첫     '[' 기호의 index
                size_t posLastOpen = line.find_last_of('[');    // 마지막 '[' 기호의 index
                size_t posClose = line.find(']');               // 첫     ']' 기호의 index
                size_t posLastClose = line.find_last_of(']');   // 마지막 ']' 기호의 index
                //cout << "posOpen: " << posOpen << "\t" << "posLastOpen: " << posLastOpen << endl;
                //cout << "posClose: " << posClose << "\t" << "posLastClose: " << posLastClose << endl;

                rows++;

                //cout << "rows 증가" << endl;

                if (posClose != posLastClose) {
                    // 마지막 행일 때만 열의 개수 확인하기
                    if (posOpen != string::npos && posClose != string::npos) {
                        string values = line.substr(posOpen + 1, posClose - posOpen - 1);
                        stringstream ss(values);
                        string value;
                        while (ss >> value) {
                            cols++;
                        }
                    }
                    break;
                }
                getline(file, line);
            }

            // matrices vector에 저장
            Matrix matrix;
            matrix.index = index;
            matrix.rows = rows;
            matrix.cols = cols;
            matrices.push_back(matrix);
            //cout << "A" << matrix.index << ": " << matrix.rows << " x " << matrix.cols << endl;
            index++;
        }
    }

    for (int i = 0; i < MATRIX_SIZE; i++) {
        cout << "A" << matrices.at(i).index << ": " << matrices.at(i).rows << " x " << matrices.at(i).cols << endl;
    }

    file.close();
}

void chainedMatrix() {
    int n = matrices.size();
    vector<vector<int>> C(n + 1, vector<int>(n + 1, 0));

    // 대각선 처리 (0으로)
    for (int i = 1; i <= n; i++) {
        C[i][i] = 0;
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            C[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = C[i][k] + C[k + 1][j] + matrices[i - 1].rows * matrices[k].cols * matrices[j - 1].cols;
                if (cost < C[i][j]) {
                    C[i][j] = cost;
                }
            }
        }
    }

    cout << setw(8) << "C";
    for (int i = 1; i <= n; i++) {
        cout << setw(8) << i;
    }
    cout << endl;

    for (int i = 1; i <= n; i++) {
        cout << setw(8) << i;
        for (int j = 1; j <= n; j++) {
            if (j >= i) {
                cout << setw(8) << C[i][j];
            }
            else {
                cout << setw(8) << "-";
            }
        }
        cout << endl;
    }
}

int main() {
    string filename = "matrix_input.txt"; // 입력 파일 이름
    // readFile(filename);
    getSize(filename);
    chainedMatrix();
    return 0;
}
