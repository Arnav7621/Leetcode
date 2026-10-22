class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        const int INF = INT_MAX;
        int ans = INF;

        // Ascending rotation: nums[i] = (i + k) % n
        int k = nums[0];
        bool asc = true;
        for (int i = 0; i < n && asc; i++)
            if (nums[i] != (i + k) % n) asc = false;
        if (asc) {
            int d = (n - k) % n;
            int cost = (d == 0) ? 0 : min(d, n - d + 2);
            ans = min(ans, cost);
        }

        // Descending rotation: nums[i] = ((k - i) mod n + n) % n
        bool desc = true;
        for (int i = 0; i < n && desc; i++)
            if (nums[i] != (((k - i) % n) + n) % n) desc = false;
        if (desc) {
            int kp = (k + 1) % n;
            int d = (n - kp) % n;
            int cost = min(d, n - d) + 1;
            ans = min(ans, cost);
        }

        return ans == INF ? -1 : ans;
    }
};