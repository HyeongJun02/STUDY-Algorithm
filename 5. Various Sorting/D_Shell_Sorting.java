import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class D_Shell_Sorting {

    // sort
    public static void shellSort(int[] A) {
        int[] gap = {100, 50, 10, 5, 1}; // Gap sequence
        int n = A.length;

        for (int h : gap) {
            for (int i = h; i < n; i++) {
                int CurrentElement = A[i];
                int j = i;
                while (j >= h && A[j - h] > CurrentElement) {
                    A[j] = A[j - h];
                    j = j - h;
                }
                A[j] = CurrentElement;
            }
        }
    }

    // read
    public static int[] read(String fileName) throws IOException {
        List<Integer> numbers = new ArrayList<>();
        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        String line;

        while ((line = reader.readLine()) != null) {
            numbers.add(Integer.parseInt(line.trim()));
        }
        reader.close();

        // array <- numbers
        int[] array = new int[numbers.size()];
        for (int i = 0; i < numbers.size(); i++) {
            array[i] = numbers.get(i);
        }
        return array;
    }

    // write
    public static void write(String fileName, int[] array) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
        for (int num : array) {
            writer.write(num + "\n");
        }
        writer.newLine();
        writer.close();
    }

    // main
    public static void main(String[] args) {
        String inputFileName = "input.txt";
        String outputFileName = "shell_output.txt";

        try {
            // read
            int[] array = read(inputFileName);

            // sort
            shellSort(array);

            // write
            write(outputFileName, array);

            System.out.println("--- 완료 ---");
            System.out.println(outputFileName);
        } catch (IOException e) {
            System.err.println("error: " + e.getMessage());
        }
    }
}
