class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {

    long long ans1 = 1LL*need1*cost1 + 1LL * need2*cost2;

    long long mini = min(need1, need2);
    long long ans2 = mini*costBoth+ 1LL*(need1 - mini)*cost1 + 1LL *( need2- mini)*cost2;

    long long ans3 = 1LL * max(need1,need2)*costBoth;
   return min({ans1, ans2, ans3});
    
    }
 
};