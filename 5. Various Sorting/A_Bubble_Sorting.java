import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class A_Bubble_Sorting {

    // sort
    public static void bubbleSort(int[] A) {
        int n = A.length;
        for (int pass = 1; pass < n; pass++) {
            for (int i = 1; i < n - pass + 1; i++) {   
                if (A[i - 1] > A[i]) {
                    int temp = A[i - 1];
                    A[i - 1] = A[i];
                    A[i] = temp;
                }
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
        String outputFileName = "bubble_output.txt";

        try {
            // read
            int[] array = read(inputFileName);

            // sort
            bubbleSort(array);

            // write
            write(outputFileName, array);

            System.out.println("--- end ---");
            System.out.println(outputFileName);

        } catch (IOException e) {
            System.err.println("error: " + e.getMessage());
        }
    }
}
