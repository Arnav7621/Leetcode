class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        
        for(int i=0; i<nums.size();i++){
            int rem,sum=0;
            if(nums[i]<10 && nums[i]==i){
                return i;
            }
           else{
                while (nums[i] > 0) {
        sum += nums[i] % 10;  
        nums[i] = nums[i] / 10; 
         }
         
            }
            if(sum==i){
                return i;
            }
           
        }
        return -1;
    }
};