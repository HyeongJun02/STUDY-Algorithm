import java.util.*;

public class B_VectorCoverProblem {

    // 그래프의 간선을 정의
    static class Edge {
        String u, v;

        Edge(String u, String v) {
            this.u = u;
            this.v = v;
        }

        @Override
        public String toString() {
            return u + "-" + v;
        }
    }

    public static void main(String[] args) {
        // Input
        List<Edge> edges = Arrays.asList(
                new Edge("A", "B"), new Edge("A", "E"), // 2
                new Edge("B", "E"), new Edge("B", "C"), new Edge("B", "F"), new Edge("B", "G"), // 6
                new Edge("C", "D"), new Edge("C", "G"), // 8
                new Edge("D", "G"), new Edge("D", "H"), // 10
                new Edge("E", "F"), new Edge("E", "I"), new Edge("E", "J"), // 13
                new Edge("F", "G"), new Edge("F", "J"), // 15
                new Edge("G", "J"), new Edge("G", "H"), new Edge("G", "K"), new Edge("G", "L"), // 19
                new Edge("H", "L"), // 20
                new Edge("I", "J"), new Edge("I", "M"), // 22
                new Edge("J", "K"), new Edge("J", "M"), new Edge("J", "N"), new Edge("J", "O"), // 26
                new Edge("K", "L"), new Edge("K", "O"), // 28
                new Edge("L", "O"), new Edge("L", "P"), // 30
                new Edge("M", "N"), new Edge("N", "O"), new Edge("O", "P") // 33
        );

        List<Edge> result = vectorCover(edges);

        for (Edge edge : result) {
            System.out.println(edge);
        }
    }

    private static List<Edge> vectorCover(List<Edge> edges) {
        List<Edge> result = new ArrayList<>();
        Set<String> verticesResult = new HashSet<>();

        edges.sort((e1, e2) -> {
            int A = e1.u.compareTo(e1.v);
            int B = e2.u.compareTo(e2.v);
            return Integer.compare(A, B);
        });

        for (Edge edge : edges) {
            if (!verticesResult.contains(edge.u) && !verticesResult.contains(edge.v)) {
                result.add(edge);
                verticesResult.add(edge.u);
                verticesResult.add(edge.v);
            }
        }

        return result;
    }
}
