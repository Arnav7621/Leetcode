class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        long long MOD = 1e9 + 7;

        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        dp[0][0] = 1;

        // Memoization table for simulation: memo[r][c][dir]
        // dir: 0 for trying to move right, 1 for trying to move down
        vector<vector<vector<pair<int, int>>>> memo(
            m, vector<vector<pair<int, int>>>(n, vector<pair<int, int>>(2, {-2, -2}))
        );

        auto simulate = [&](auto& self, int r, int c, int dir) -> pair<int, int> {
            if (memo[r][c][dir].first != -2) return memo[r][c][dir];
            
            int cr = r, cc = c, cd = dir;
            while (true) {
                if (cd == 0) {
                    cc++;
                    if (cc >= n) return memo[r][c][dir] = {-1, -1};
                    if (grid[cr][cc] == 0) return memo[r][c][dir] = {cr, cc};
                    cd = 1; // Hit mirror while moving right -> turn down
                } else {
                    cr++;
                    if (cr >= m) return memo[r][c][dir] = {-1, -1};
                    if (grid[cr][cc] == 0) return memo[r][c][dir] = {cr, cc};
                    cd = 0; // Hit mirror while moving down -> turn right
                }
            }
        };

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (dp[r][c] == 0) continue;
                if (r == m - 1 && c == n - 1) continue;

                // Try moving Right (dir = 0)
                auto next_r = simulate(simulate, r, c, 0);
                if (next_r.first != -1) {
                    dp[next_r.first][next_r.second] = (dp[next_r.first][next_r.second] + dp[r][c]) % MOD;
                }

                // Try moving Down (dir = 1)
                auto next_d = simulate(simulate, r, c, 1);
                if (next_d.first != -1) {
                    dp[next_d.first][next_d.second] = (dp[next_d.first][next_d.second] + dp[r][c]) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};