class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length();

        vector<int> dp(n, 0);
        int ans = 0;

        for (int i = 1; i < n; i++) {

            if (s[i] == ')') {

                // Case 1: "()"
                if (s[i - 1] == '(') {
                    dp[i] = 2;

                    if (i >= 2) {
                        dp[i] += dp[i - 2];
                    }
                }

                // Case 2: "(...))"
                else if (dp[i - 1] > 0) {

                    int open = i - dp[i - 1] - 1;

                    if (open >= 0 && s[open] == '(') {

                        dp[i] = dp[i - 1] + 2;

                        if (open >= 1) {
                            dp[i] += dp[open - 1];
                        }
                    }
                }

                ans = max(ans, dp[i]);
            }
        }

        return ans;
    }
};