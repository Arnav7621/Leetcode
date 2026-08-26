class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {

        int n = s.size();
        int left = 0;
        int ones = 0;

        string ans = "";

        for(int right = 0; right < n; right++) {

            if(s[right] == '1')
                ones++;

            // Too many 1s
            while(ones > k) {
                if(s[left] == '1')
                    ones--;
                left++;
            }

            // Exactly k ones
            if(ones == k) {

                // Remove unnecessary 0s from the left
                while(left <= right && s[left] == '0')
                    left++;

                string curr = s.substr(left, right - left + 1);

                if(ans == "" ||
                   curr.size() < ans.size() ||
                   (curr.size() == ans.size() && curr < ans)) {

                    ans = curr;
                }
            }
        }

        return ans;
    }
};