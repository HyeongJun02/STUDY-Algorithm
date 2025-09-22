import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.time.Duration;
import java.time.Instant;

public class B_QuickSort {

    // Quick Sort 구현
    public static void quickSort(int[] array, int left, int right) {
        if (left < right) {
            int pivotIndex = partition(array, left, right);
            quickSort(array, left, pivotIndex - 1);
            quickSort(array, pivotIndex + 1, right);
        }
    }

    private static int partition(int[] array, int left, int right) {
        int pivot = array[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (array[j] <= pivot) {
                i++;
                swap(array, i, j);
            }
        }
        swap(array, i + 1, right);
        return i + 1;
    }

    private static void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // 출력하는 부분
    public static void writeToTxt(int[] sortedArray, String outputFileName) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(outputFileName));
        for (int num : sortedArray) {
            writer.write(num + "\n");
        }
        writer.close();
    }

    public static void main(String[] args) {
        try {
            // 파일 읽기 시작 시간
            Instant start = Instant.now();

            // 파일 읽기
            List<String> lines = Files.readAllLines(Paths.get("input_sort.txt"));
            int[] numbers = lines.stream().mapToInt(Integer::parseInt).toArray();

            // 정렬 시작 시간
            Instant sortStart = Instant.now();
            quickSort(numbers, 0, numbers.length - 1);
            Instant sortEnd = Instant.now();

            // 파일 출력
            String outputFileName = "B_QuickSort.txt";
            writeToTxt(numbers, outputFileName);

            // 전체 종료 시간
            Instant end = Instant.now();

            Duration fileIoTime = Duration.between(start, sortStart);
            Duration sortTime = Duration.between(sortStart, sortEnd);
            Duration outputTime = Duration.between(sortEnd, end);
            Duration totalTime = Duration.between(start, end);

            System.out.println("파일 읽기 시간: " + fileIoTime.toMillis() + " ms");
            System.out.println("정렬 시간: " + sortTime.toMillis() + " ms");
            System.out.println("파일 출력 시간: " + outputTime.toMillis() + " ms");
            System.out.println("전체 실행 시간: " + totalTime.toMillis() + " ms");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
