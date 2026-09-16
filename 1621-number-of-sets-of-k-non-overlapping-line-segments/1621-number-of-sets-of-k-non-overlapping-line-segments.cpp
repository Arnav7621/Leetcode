class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1e9 + 7;

        vector<vector<long long>> dp(k + 1, vector<long long>(n, 0));

        // 0 segments: 1 way
        for (int i = 0; i < n; i++)
            dp[0][i] = 1;

        for (int seg = 1; seg <= k; seg++) {
            long long sum = 0;

            for (int i = 1; i < n; i++) {
                sum = (sum + dp[seg - 1][i - 1]) % MOD;
                dp[seg][i] = (dp[seg][i - 1] + sum) % MOD;
            }
        }

        return dp[k][n - 1];
    }
};