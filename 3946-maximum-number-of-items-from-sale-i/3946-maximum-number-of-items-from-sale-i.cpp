
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        // Step 1: Calculate the free items for each item
        vector<int> val(n, 1);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    val[i]++;
                }
            }
        }

        // Step 2: Group items according to their price
        vector<vector<int>> groups(budget + 1);

        for (int i = 0; i < n; i++) {
            int price = items[i][1];

            if (price <= budget) {
                groups[price].push_back(i);
            }
        }

        // dp[c] = maximum value using items with
        // prices strictly greater than current price
        // and spending exactly c.
        const int NEG = -1e9;

        vector<int> dp(budget + 1, NEG);
        dp[0] = 0;

        int ans = 0;

        // Step 3: Process prices in descending order
        for (int p = budget; p >= 1; p--) {

            if (groups[p].empty()) continue;

            // dp1: Must select at least one item
            // having price exactly p.
            vector<int> dp1(budget + 1, NEG);

            for (int idx : groups[p]) {
                int price = items[idx][1];
                int value = val[idx];

                // 0/1 knapsack transition
                for (int c = budget; c >= price; c--) {

                    if (dp1[c - price] != NEG) {
                        dp1[c] = max(
                            dp1[c],
                            dp1[c - price] + value
                        );
                    }

                    if (dp[c - price] != NEG) {
                        dp1[c] = max(
                            dp1[c],
                            dp[c - price] + value
                        );
                    }
                }
            }

            // Step 4: Calculate the maximum answer
            for (int c = 0; c <= budget; c++) {
                if (dp1[c] == NEG) continue;

                int extra = (budget - c) / p;

                ans = max(ans, dp1[c] + extra);
            }

            // Step 5: Add current price group to normal DP
            // for processing smaller prices.
            for (int idx : groups[p]) {
                int price = items[idx][1];
                int value = val[idx];

                for (int c = budget; c >= price; c--) {
                    if (dp[c - price] != NEG) {
                        dp[c] = max(
                            dp[c],
                            dp[c - price] + value
                        );
                    }
                }
            }
        }

        return ans;
    }
};
