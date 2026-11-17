
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        vector<vector<int>> cost(n, vector<int>(n, INF));

        // Precompute minimum changes for every substring
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int len = j - i + 1;

                for(int d = 1; d < len; d++) {
                    if(len % d != 0) continue;

                    int changes = 0;

                    for(int p = 0; p < d; p++) {
                        int cnt = (len - 1 - p) / d + 1;

                        for(int q = 0; q < cnt / 2; q++) {
                            int a = i + p + q * d;
                            int b = i + p + (cnt - 1 - q) * d;

                            if(s[a] != s[b]) {
                                changes++;
                            }
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // DP: minimum changes to divide first j characters into parts
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));

        dp[0][0] = 0;

        for(int parts = 1; parts <= k; parts++) {
            for(int j = 2 * parts; j <= n; j++) {
                for(int i = 2 * (parts - 1); i <= j - 2; i++) {
                    if(dp[parts - 1][i] != INF) {
                        dp[parts][j] = min(
                            dp[parts][j],
                            dp[parts - 1][i] + cost[i][j - 1]
                        );
                    }
                }
            }
        }

        return dp[k][n];
    }
};
