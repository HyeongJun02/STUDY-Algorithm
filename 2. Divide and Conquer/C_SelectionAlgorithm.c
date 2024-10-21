#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TARGET_1 50
#define TARGET_2 70

// k번째로 작은 값을 찾기 위한 선택 알고리즘 (Quickselect 기반)
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;

    return i + 1;
}

int quickSelect(int arr[], int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }

    int pivotIndex = partition(arr, left, right);

    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quickSelect(arr, left, pivotIndex - 1, k);
    } else {
        return quickSelect(arr, pivotIndex + 1, right, k);
    }
}

int main() {
    FILE *file;
    int *numbers;
    int count = 0;
    char buffer[256];
    
    // 시간 측정
    clock_t start = clock();
    
    // 파일 읽기
    file = fopen("input_sort.txt", "r");
    if (file == NULL) {
        printf("file open Fail!!!!\n");
        return 1;
    }

    // 데이터 읽기
    while (fgets(buffer, sizeof(buffer), file)) {
        count++;
    }

    // 파일 포인터를 다시 파일의 시작으로 설정
    rewind(file);

    numbers = (int *)malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        fscanf(file, "%d", &numbers[i]);
    }

    fclose(file);

    // 선택 알고리즘 적용 시작 시간 측정
    clock_t select_start = clock();

    // 50번째, 70번째 찾아보자
    int target1 = quickSelect(numbers, 0, count - 1, TARGET_1 - 1);
    int target2 = quickSelect(numbers, 0, count - 1, TARGET_2 - 1);

    // 선택 알고리즘 완료 시간 측정
    clock_t select_end = clock();

    // 결과 출력
    printf("50번째: %d\n", target1);
    printf("70번째: %d\n", target2);

    // 시간 측정 종료
    clock_t end = clock();

    // 시간 출력
    double file_read_time = (double)(select_start - start) / CLOCKS_PER_SEC * 1000;
    double selection_time = (double)(select_end - select_start) / CLOCKS_PER_SEC * 1000;
    double total_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;

    printf("파일 읽기 시간: %.2f ms\n", file_read_time);
    printf("Select Algorithm 실행 시간: %.2f ms\n", selection_time);
    printf("전체 실행 시간: %.2f ms\n", total_time);

    free(numbers);

    return 0;
}
