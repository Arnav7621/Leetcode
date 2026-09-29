class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // A valid parentheses string must have even length
        if ((m + n - 1) % 2 == 1)
            return false;

        // dp[i][j][balance] = whether we can reach (i,j)
        // with the given balance
        vector<vector<vector<bool>>> dp(
            m, vector<vector<bool>>(n, vector<bool>(m + n, false))
        );

        // Starting cell must be '('
        if (grid[0][0] == ')')
            return false;

        dp[0][0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                for (int balance = 0; balance <= m + n; balance++) {

                    if (grid[i][j] == '(') {

                        // Previous balance must be balance - 1
                        if (balance > 0) {
                            if (i > 0 && dp[i - 1][j][balance - 1])
                                dp[i][j][balance] = true;

                            if (j > 0 && dp[i][j - 1][balance - 1])
                                dp[i][j][balance] = true;
                        }

                    } else {

                        // ')' decreases balance
                        if (balance < m + n) {
                            if (i > 0 && dp[i - 1][j][balance + 1])
                                dp[i][j][balance] = true;

                            if (j > 0 && dp[i][j - 1][balance + 1])
                                dp[i][j][balance] = true;
                        }
                    }
                }
            }
        }

        return dp[m - 1][n - 1][0];
    }
};