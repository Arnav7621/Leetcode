class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 2; // Any subarray of length 2 satisfies prod == lcm * gcd

        int primes[] = {2, 3, 5, 7};
        int cnt[4] = {0};
        int left = 0;

        for (int right = 0; right < n; right++) {
            for (int p = 0; p < 4; p++) {
                if (nums[right] % primes[p] == 0) {
                    cnt[p]++;
                }
            }

            // For length >= 3, each prime can appear at most ONCE
            while (cnt[0] > 1 || cnt[1] > 1 || cnt[2] > 1 || cnt[3] > 1) {
                for (int p = 0; p < 4; p++) {
                    if (nums[left] % primes[p] == 0) {
                        cnt[p]--;
                    }
                }
                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};