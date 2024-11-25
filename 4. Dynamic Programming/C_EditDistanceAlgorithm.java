public class C_EditDistanceAlgorithm {

    public static void findEditDistance(String S, String T) {
        int m = S.length();
        int n = T.length();
        int[][] dp = new int[m + 1][n + 1];

        // 1
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        // 2
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        // 3
        for (int i = 1; i <= m; i++) {
            // 4
            for (int j = 1; j <= n; j++) {
                // 5
                if (S.charAt(i - 1) == T.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1]; // alpha = 0
                } else {
                    dp[i][j] = Math.min(
                        Math.min(dp[i - 1][j] + 1, // 삭제
                                 dp[i][j - 1] + 1), // 삽입
                        dp[i - 1][j - 1] + 1 // 대체
                    );
                }
            }
        }

        // --------------------- 출력 ---------------------
        System.out.print("  ε  ");
        for (int j = 0; j < n; j++) {
            System.out.print(T.charAt(j) + "  ");
        }
        System.out.println();

        for (int i = 0; i <= m; i++) {
            if (i == 0) {
                System.out.print("ε ");
            } else {
                System.out.print(S.charAt(i - 1) + " ");
            }
            for (int j = 0; j <= n; j++) {
                System.out.printf("%2d ", dp[i][j]);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        String S = "strong";
        String T = "stone";
        findEditDistance(S, T);
    }
}
