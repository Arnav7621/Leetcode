
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        vector<long long> dup;
        
        for (int x : nums) {
            dup.push_back(1LL * x * x);
        }

        sort(dup.begin(), dup.end());

        int n = dup.size();
        long long ans = 0;

        for (int i = 0; i < n / 2; i++) {
            ans -= dup[i];
        }

        for (int i = n / 2; i < n; i++) {
            ans += dup[i];
        }

        return ans;
    }
};
