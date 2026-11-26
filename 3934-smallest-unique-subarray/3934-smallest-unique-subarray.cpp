class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        const uint64_t MOD1 = 1000000007ULL;
        const uint64_t MOD2 = 1000000009ULL;
        const uint64_t BASE1 = 1315423911ULL % MOD1;
        const uint64_t BASE2 = 2654435761ULL % MOD2;

        // Precompute powers and prefix hashes
        vector<uint64_t> p1(n + 1, 1), p2(n + 1, 1);
        vector<uint64_t> h1(n + 1, 0), h2(n + 1, 0);

        for (int i = 0; i < n; i++) {
            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
            h1[i + 1] = (h1[i] * BASE1 + nums[i]) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + nums[i]) % MOD2;
        }

        auto hasUniqueOfLength = [&](int len) -> bool {
            int count = n - len + 1;
            vector<uint64_t> hashes;
            hashes.reserve(count);

            for (int i = 0; i < count; i++) {
                uint64_t sub1 = (h1[i + len] + MOD1 - (h1[i] * p1[len]) % MOD1) % MOD1;
                uint64_t sub2 = (h2[i + len] + MOD2 - (h2[i] * p2[len]) % MOD2) % MOD2;
                hashes.push_back((sub1 << 32) | sub2);
            }

            // Sorting avoids unordered_map overhead and worst-case hash collisions
            sort(hashes.begin(), hashes.end());

            for (int i = 0; i < count; i++) {
                bool sameAsPrev = (i > 0 && hashes[i] == hashes[i - 1]);
                bool sameAsNext = (i + 1 < count && hashes[i] == hashes[i + 1]);
                if (!sameAsPrev && !sameAsNext) {
                    return true;
                }
            }
            return false;
        };

        int low = 1, high = n, ans = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hasUniqueOfLength(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};