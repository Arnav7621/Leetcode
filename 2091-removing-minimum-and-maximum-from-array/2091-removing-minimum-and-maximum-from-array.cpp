class Solution {
public:
    int minimumDeletions(vector<int>& nums) {

        int n = nums.size();

        int mn = 0, mx = 0;

        for(int i = 0; i < n; i++) {
            if(nums[i] < nums[mn])
                mn = i;

            if(nums[i] > nums[mx])
                mx = i;
        }

        // Make mn the smaller index
        if(mn > mx)
            swap(mn, mx);

        // Both from front
        int front = mx + 1;

        // Both from back
        int back = n - mn;

        // One from front, one from back
        int both = (mn + 1) + (n - mx);

        return min({front, back, both});
    }
};