import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class A_Bubble_Sorting {

    // sort
    public static void bubbleSort(int[] array) {
        int n = array.length;
        boolean flag;
        for (int i = 0; i < n - 1; i++) {
            flag = false;
            for (int j = 0; j < n - i - 1; j++) {   
                if (array[j] > array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    flag = true;
                }
            }
            if (!flag) break;
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
