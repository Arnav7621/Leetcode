#include <vector>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
    long long memo[100005][16];
    const long long INF = 1e18;

    // Dynamic Programming to choose k non-overlapping windows
    long long solve(int i, int remaining_k, int x, const vector<long long>& cost, int n) {
        if (remaining_k == 0) return 0;
        if (i > n - x) return INF; // Not enough space left to pick a window of size x

        if (memo[i][remaining_k] != -1) return memo[i][remaining_k];

        // Option 1: Skip current index
        long long skip = solve(i + 1, remaining_k, x, cost, n);

        // Option 2: Pick subarray of size x starting at i
        long long pick = cost[i] + solve(i + x, remaining_k - 1, x, cost, n);

        return memo[i][remaining_k] = min(skip, pick);
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        vector<long long> cost(n, 0);

        // Multisets to maintain median of sliding window of size x
        multiset<long long> lower, upper;
        long long lowerSum = 0, upperSum = 0;

        for (int i = 0; i < n; ++i) {
            // Add current element
            if (lower.empty() || nums[i] <= *lower.rbegin()) {
                lower.insert(nums[i]);
                lowerSum += nums[i];
            } else {
                upper.insert(nums[i]);
                upperSum += nums[i];
            }

            // Remove element falling out of the window of size x
            if (i >= x) {
                long long out = nums[i - x];
                auto it = lower.find(out);
                if (it != lower.end()) {
                    lower.erase(it);
                    lowerSum -= out;
                } else {
                    upper.erase(upper.find(out));
                    upperSum -= out;
                }
            }

            // Balance multisets so that lower always has ceil(x / 2) elements
            while (lower.size() < upper.size()) {
                long long val = *upper.begin();
                upper.erase(upper.begin());
                upperSum -= val;
                lower.insert(val);
                lowerSum += val;
            }
            while (lower.size() > upper.size() + 1) {
                long long val = *lower.rbegin();
                lower.erase(prev(lower.end()));
                lowerSum -= val;
                upper.insert(val);
                upperSum += val;
            }

            // Calculate cost for subarray ending at i (starting at i - x + 1)
            if (i >= x - 1) {
                long long median = *lower.rbegin();
                long long currentCost = (median * lower.size() - lowerSum) + 
                                        (upperSum - median * upper.size());
                cost[i - x + 1] = currentCost;
            }
        }

        // Initialize memoization array
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                memo[i][j] = -1;
            }
        }

        return solve(0, k, x, cost, n);
    }
};