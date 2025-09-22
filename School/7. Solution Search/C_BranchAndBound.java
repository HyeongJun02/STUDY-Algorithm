import java.util.PriorityQueue;

class Node implements Comparable<Node> {
    int level;
    int[] tour;
    int cost;
    int bound;

    Node(int level, int[] tour, int cost, int bound) {
        this.level = level;
        this.tour = tour;
        this.cost = cost;
        this.bound = bound;
    }

    @Override
    public int compareTo(Node other) {
        return this.bound - other.bound;
    }
}

public class C_BranchAndBound {

    static final int N = 5;
    static int[][] graph = {
        {0, 2, 7, 3, 10},
        {2, 0, 3, 5, 4},
        {7, 3, 0, 6, 1},
        {3, 5, 6, 0, 9},
        {10, 4, 1, 9, 0}
    };

    static int[] result;
    static int minimum = Integer.MAX_VALUE;

    public static void tsp() {
        PriorityQueue<Node> pq = new PriorityQueue<>();
        int[] tour = new int[N];
        for (int i = 0; i < N; i++) {
            tour[i] = -1;
        }
        tour[0] = 0;

        Node root = new Node(1, tour, 0, calculateBound(tour, 0, 1));
        pq.add(root);

        while (!pq.isEmpty()) {
            Node current = pq.poll();

            if (current.bound >= minimum) continue;

            if (current.level == N) {
                int distance = current.cost + graph[current.tour[N - 1]][current.tour[0]];
                if (distance < minimum) {
                    minimum = distance;
                    result = current.tour.clone();
                }
                continue;
            }

            for (int v = 1; v < N; v++) {
                if (!isInTour(current.tour, v)) {
                    int[] newTour = current.tour.clone();
                    newTour[current.level] = v;

                    int newCost = current.cost + graph[current.tour[current.level - 1]][v];
                    int newBound = calculateBound(newTour, newCost, current.level + 1);

                    if (newBound < minimum) {
                        pq.add(new Node(current.level + 1, newTour, newCost, newBound));
                    }
                }
            }
        }
    }

    private static boolean isInTour(int[] tour, int city) {
        for (int i : tour) {
            if (i == city) return true;
        }
        return false;
    }

    private static int calculateBound(int[] tour, int cost, int level) {
        int bound = cost;

        boolean[] visited = new boolean[N];
        for (int i = 0; i < level; i++) {
            visited[tour[i]] = true;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                int minEdge = Integer.MAX_VALUE;
                for (int j = 0; j < N; j++) {
                    if (i != j && !visited[j] && graph[i][j] > 0) {
                        minEdge = Math.min(minEdge, graph[i][j]);
                    }
                }
                bound += minEdge;
            }
        }
        return bound;
    }

    public static void main(String[] args) {
        tsp();

        System.out.print("[");
        for (int i = 0; i < N; i++) {
            System.out.print((char) ('A' + result[i]) + ",");
        }
        System.out.print("A], ");
        System.out.println("거리 = " + minimum);
    }
}
