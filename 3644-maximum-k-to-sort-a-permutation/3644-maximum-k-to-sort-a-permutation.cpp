
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int ans = -1;
        bool sorted = true;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i) {
                ans &= nums[i];
                sorted = false;
            }
        }

        return sorted ? 0 : ans;
    }
};
