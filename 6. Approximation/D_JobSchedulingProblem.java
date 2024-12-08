import java.util.PriorityQueue;

public class D_JobSchedulingProblem {

    static class Machine {
        int id;
        int endTime;

        Machine(int id, int endTime) {
            this.id = id;
            this.endTime = endTime;
        }
    }

    public static void main(String[] args) {
        int m = 4;
        int[] operationTime = {5, 2, 4, 3, 4, 7, 9, 2, 4, 1};
        int n = operationTime.length;

        PriorityQueue<Machine> mQueue = new PriorityQueue<>((a, b) -> a.endTime - b.endTime);

        for (int i = 1; i <= m; i++) {
            mQueue.add(new Machine(i, 0));
        }

        StringBuilder[] schedule = new StringBuilder[m];
        for (int i = 0; i < m; i++) {
            schedule[i] = new StringBuilder();
        }

        for (int i = 0; i < n; i++) {
            Machine now = mQueue.poll();

            schedule[now.id - 1].append("t").append(i + 1)
                    .append("(").append(now.endTime)
                    .append("-").append(now.endTime + operationTime[i]).append(") ");
            now.endTime += operationTime[i];

            mQueue.add(now);
        }

        for (int i = 0; i < m; i++) {
            System.out.println("m" + (i + 1) + ": " + schedule[i]);
        }
    }
}
