#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <chrono>

#define MAX_SIZE 1000

using namespace std;
using namespace chrono;

int sorted[MAX_SIZE];

// merge 함수
void merge(vector<int>& list, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    // 분할 정렬 완료한 list 합병
    while (i <= mid && j <= right) {
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
    }

    // 값 복사요
    while (i <= mid) {
        sorted[k++] = list[i++];
    }
    while (j <= right) {
        sorted[k++] = list[j++];
    }

    // list <- sorted
    for (k = left; k <= right; k++) {
        list[k] = sorted[k];
    }
}

// merge sort 함수
void merge_sort(vector<int>& list, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2; // 중앙은 여기에요
        merge_sort(list, left, mid); // 앞 정렬
        merge_sort(list, mid + 1, right); // 뒤 정렬
        merge(list, left, mid, right); // 합치기
    }
}

int main() {
    vector<int> numbers;

    // 파일 읽기 시작 시간
    auto start = high_resolution_clock::now();

    ifstream file("input_sort.txt");
    if (!file.is_open()) {
        cerr << "[ERROR] File Open" << endl;
        return 1;
    }

    int num;
    while (file >> num) {
        numbers.push_back(num);
    }
    file.close();

    // 정렬 시작 시간
    auto sort_start = high_resolution_clock::now();
    merge_sort(numbers, 0, numbers.size() - 1);
    auto sort_end = high_resolution_clock::now();

    // 파일 출력 시작 시간
    ofstream output("A_MergeSort.txt");
    if (!output.is_open()) {
        cerr << "File Open Fail!!!!!!!!!!!!!" << endl;
        return 1;
    }

    for (size_t i = 0; i < numbers.size(); i++) {
        output << numbers[i];
        if (i != numbers.size() - 1) {
            output << "\n";
        }
    }
    output.close();

    // 전체 종료 시간
    auto end = high_resolution_clock::now();

    // 시간 계산
    auto file_io_time = duration_cast<milliseconds>(sort_start - start).count();
    auto sort_time = duration_cast<milliseconds>(sort_end - sort_start).count();
    auto output_time = duration_cast<milliseconds>(end - sort_end).count();
    auto total_time = duration_cast<milliseconds>(end - start).count();

    // 시간 출력
    cout << "파일 읽기 시간: " << file_io_time << " ms" << endl;
    cout << "정렬 시간: " << sort_time << " ms" << endl;
    cout << "파일 출력 시간: " << output_time << " ms" << endl;
    cout << "전체 실행 시간: " << total_time << " ms" << endl;

    return 0;
}
