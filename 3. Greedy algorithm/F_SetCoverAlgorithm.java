import java.util.*;

public class F_SetCoverAlgorithm {
    public static void main(String[] args) {
        // 그래프 정의 (각 마을의 연결된 마을 리스트)
        Map<Integer, List<Integer>> graph = new HashMap<>();
        graph.put(1, new ArrayList<>(Arrays.asList(2, 3, 8)));
        graph.put(2, new ArrayList<>(Arrays.asList(1, 3, 4, 8)));
        graph.put(3, new ArrayList<>(Arrays.asList(1, 2, 4)));
        graph.put(4, new ArrayList<>(Arrays.asList(2, 3, 5, 7, 8)));
        graph.put(5, new ArrayList<>(Arrays.asList(4, 6, 7)));
        graph.put(6, new ArrayList<>(Arrays.asList(5, 7, 9, 10)));
        graph.put(7, new ArrayList<>(Arrays.asList(4, 5, 6)));
        graph.put(8, new ArrayList<>(Arrays.asList(1, 2, 4)));
        graph.put(9, new ArrayList<>(Arrays.asList(6)));
        graph.put(10, new ArrayList<>(Arrays.asList(6)));

        // System.out.println("graph: " + graph);

        long startTime = System.currentTimeMillis();
        Set<Integer> setCover = findSetCover(graph);
        long endTime = System.currentTimeMillis();

        System.out.println("C = " + setCover);
        System.out.println("Running time: " + (endTime - startTime) + " ms");
    }

    public static Set<Integer> findSetCover(Map<Integer, List<Integer>> graph) {
        Set<Integer> setCover = new HashSet<>();
        Set<Integer> covered = new HashSet<>();  // 이미 커버된 마을들

        // 모든 마을이 커버될 때까지 반복
        while (graph.size() > 0) {
            // int maxNode = -1;       // 가장 많은 마을을 커버할 수 있는 마을
            // int maxNeighbors = -1;  // 가장 많은 연결된 마을 수

            int max_key = 0;        // 가장 많은 점을 보유한 지점 key
            int max_size = 0;       // 가장 많은 점을 보유한 지점 size

            for (Map.Entry<Integer, List<Integer>> entry : graph.entrySet()) {
                int key = entry.getKey();
                int size = entry.getValue().size();

                if (size > max_size) {
                    max_size = size;
                    max_key = key;
                }
            }
            // System.out.println("max_key: " + max_key);

            setCover.add(max_key);
            covered.add(max_key);

            List<Integer> delete_value = new ArrayList<>(graph.get(max_key));
            // System.out.println("delete_value: " + delete_value);

            graph.remove(max_key);
            // System.out.println("graph: " + graph);

            for (Iterator<Map.Entry<Integer, List<Integer>>> it = graph.entrySet().iterator(); it.hasNext();) {
                Map.Entry<Integer, List<Integer>> entry = it.next();
                if (delete_value.contains(entry.getKey())) {
                    it.remove();
                }
            }

        }
        return setCover;
    }
}
