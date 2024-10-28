import java.util.*;

class C_PrimAlgorithm {
    static class Edge implements Comparable<Edge> {
        int vertex1, vertex2, weight;

        Edge(int vertex1, int vertex2, int weight) {
            this.vertex1 = vertex1;
            this.vertex2 = vertex2;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge other) {
            return this.weight - other.weight;
        }
    }

    public static void main(String[] args) {
        int numVertices = 6;
        List<Edge>[] graph = new List[numVertices];
        for (int i = 0; i < numVertices; i++) {
            graph[i] = new ArrayList<>();
        }

        // Input
        addEdge(graph, 0, 3, 2); // a-d: 2
        addEdge(graph, 0, 4, 4); // a-e: 4
        addEdge(graph, 1, 0, 3); // b-a: 3
        addEdge(graph, 1, 3, 4); // b-d: 4
        addEdge(graph, 1, 5, 2); // b-f: 2
        addEdge(graph, 2, 1, 1); // c-b: 1
        addEdge(graph, 2, 5, 1); // c-f: 1
        addEdge(graph, 3, 4, 5); // d-e: 5
        addEdge(graph, 3, 5, 7); // d-f: 7
        addEdge(graph, 4, 5, 9); // e-f: 9

        // 실행
        long startTime = System.currentTimeMillis();
        prim(graph, numVertices);
        long endTime = System.currentTimeMillis();

        // running time
        System.out.println("Running time: " + (endTime - startTime) + " ms");
    }

    static void addEdge(List<Edge>[] graph, int v1, int v2, int weight) {
        graph[v1].add(new Edge(v1, v2, weight));
        graph[v2].add(new Edge(v2, v1, weight));
    }

    static void prim(List<Edge>[] graph, int numVertices) {
        boolean[] visited = new boolean[numVertices];
        PriorityQueue<Edge> pq = new PriorityQueue<>();
        List<Edge> mst = new ArrayList<>();

        visited[0] = true;
        pq.addAll(graph[0]);

        while (!pq.isEmpty() && mst.size() < numVertices - 1) {
            Edge edge = pq.poll();

            if (!visited[edge.vertex2]) {
                visited[edge.vertex2] = true;
                mst.add(edge);
                pq.addAll(graph[edge.vertex2]);
            }
        }

        for (Edge edge : mst) {
            System.out.println("(" + edge.vertex1 + ", " + edge.vertex2 + ", " + edge.weight + ")");
        }
    }
}
