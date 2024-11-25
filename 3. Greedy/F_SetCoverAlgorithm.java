import java.util.*;

public class F_SetCoverAlgorithm {
    public static void main(String[] args) {
        // 그래프 정의 (각 마을의 연결된 마을 리스트)
        Map<Integer, List<Integer>> node = new HashMap<>();
        node.put(1, new ArrayList<>(Arrays.asList(2, 3, 8)));
        node.put(2, new ArrayList<>(Arrays.asList(1, 3, 4, 8)));
        node.put(3, new ArrayList<>(Arrays.asList(1, 2, 4)));
        node.put(4, new ArrayList<>(Arrays.asList(2, 3, 5, 7, 8)));
        node.put(5, new ArrayList<>(Arrays.asList(4, 6, 7)));
        node.put(6, new ArrayList<>(Arrays.asList(5, 7, 9, 10)));
        node.put(7, new ArrayList<>(Arrays.asList(4, 5, 6)));
        node.put(8, new ArrayList<>(Arrays.asList(1, 2, 4)));
        node.put(9, new ArrayList<>(Arrays.asList(6)));
        node.put(10, new ArrayList<>(Arrays.asList(6)));

        Map<Integer, List<Integer>> set_cover_node = new HashMap<>(node);
        Map<Integer, List<Integer>> optimal_node = new HashMap<>(node);

        long startTime = System.currentTimeMillis();
        Set<Integer> setCover = setCover(set_cover_node);
        long endTime = System.currentTimeMillis();

        System.out.println("<Set Cover>");
        System.out.println("C = " + setCover);
        System.out.println("Running time: " + (endTime - startTime) + " ms");
        
        System.out.println("");

        long optimalStartTime = System.currentTimeMillis();
        Set<Integer> optimalSetCover = optimalSetCover(optimal_node);
        long optimalEndTime = System.currentTimeMillis();

        System.out.println("<Set Cover - Optimal Solution>");
        System.out.println("C = " + optimalSetCover);
        System.out.println("Running time: " + (optimalEndTime - optimalStartTime) + " ms");
    }

    public static Set<Integer> setCover(Map<Integer, List<Integer>> set_cover_node) {
        Set<Integer> setCover = new HashSet<>();

        // 모든 마을이 커버될 때까지 반복
        while (set_cover_node.size() > 0) {
            int max_key = 0;        // 가장 많은 점을 보유한 지점 key
            int max_size = 0;       // 가장 많은 점을 보유한 지점 size

            for (Map.Entry<Integer, List<Integer>> entry : set_cover_node.entrySet()) {
                int key = entry.getKey();
                int size = entry.getValue().size();

                if (size > max_size) {
                    max_size = size;
                    max_key = key;
                }
            }
            // System.out.println("max_key: " + max_key);

            setCover.add(max_key);

            List<Integer> delete_value = new ArrayList<>(set_cover_node.get(max_key));
            // System.out.println("delete_value: " + delete_value);

            set_cover_node.remove(max_key);
            // System.out.println("set_cover_node: " + set_cover_node);

            for (Iterator<Map.Entry<Integer, List<Integer>>> it = set_cover_node.entrySet().iterator(); it.hasNext();) {
                Map.Entry<Integer, List<Integer>> entry = it.next();
                if (delete_value.contains(entry.getKey())) {
                    it.remove();
                }
            }
        }
        return setCover;
    }

    public static Set<Integer> optimalSetCover(Map<Integer, List<Integer>> optimal_node) {
        Set<Integer> best = null;
        int min_size = Integer.MAX_VALUE;

        // 그냥 다 해
        List<Integer> nodes = new ArrayList<>(optimal_node.keySet());
        int n = nodes.size();
        for (int i = 1; i < (1 << n); i++) {
            Set<Integer> candidateSet = new HashSet<>();
            Set<Integer> covered = new HashSet<>();

            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) != 0) {
                    int node = nodes.get(j);
                    candidateSet.add(node);
                    covered.add(node);
                    covered.addAll(optimal_node.get(node));
                }
            }

            if (covered.size() == n && candidateSet.size() < min_size) {
                min_size = candidateSet.size();
                best = new HashSet<>(candidateSet);
            }
        }

        return best;
    }
}
