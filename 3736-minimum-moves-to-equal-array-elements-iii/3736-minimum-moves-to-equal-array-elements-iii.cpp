class Solution {
public:
    int minMoves(vector<int>& nums) {
        int step = 0, n = nums.size();
        sort(nums.begin(), nums.end());

        int maxi = nums[n-1];

        for(int i = 0; i < n-1; i++) {
            step += maxi - nums[i];
        }

        return step;
    }
};