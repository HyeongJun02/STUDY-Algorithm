import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class A_Bubble_Sorting {

    // Bubble Sort 구현
    public static void bubbleSort(int[] array) {
        int n = array.length;
        boolean swapped;
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    // 두 원소를 교환
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    swapped = true;
                }
            }
            // 더 이상 교환이 없으면 정렬 완료
            if (!swapped) break;
        }
    }

    // 파일로부터 데이터를 읽어오기
    public static int[] readInputFile(String fileName) throws IOException {
        List<Integer> numbers = new ArrayList<>();
        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        String line;
        while ((line = reader.readLine()) != null) {
            String[] parts = line.split("\\s+"); // 공백으로 구분
            for (String part : parts) {
                numbers.add(Integer.parseInt(part)); // 정수로 변환 후 추가
            }
        }
        reader.close();

        // 리스트를 배열로 변환
        int[] array = new int[numbers.size()];
        for (int i = 0; i < numbers.size(); i++) {
            array[i] = numbers.get(i);
        }
        return array;
    }

    // 정렬된 결과를 파일로 쓰기
    public static void writeOutputFile(String fileName, int[] array) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
        for (int num : array) {
            writer.write(num + " ");
        }
        writer.newLine();
        writer.close();
    }

    // 메인 함수
    public static void main(String[] args) {
        String inputFileName = "input.txt";
        String outputFileName = "bubble_output.txt";

        try {
            // 입력 파일 읽기
            int[] array = readInputFile(inputFileName);

            // Bubble Sort 수행
            bubbleSort(array);

            // 출력 파일 작성
            writeOutputFile(outputFileName, array);

            System.out.println("Bubble sort completed. Results are saved in " + outputFileName);

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}
