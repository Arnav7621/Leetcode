
class Solution {
public:
    int minOperations(string s) {
        string t = s;
        sort(t.begin(), t.end());

        if (s == t) return 0;

        int n = s.size();

        if (n == 2) return -1;

        char mn = t[0], mx = t[n - 1];

        bool firstMin = (s[0] == mn);
        bool lastMax = (s[n - 1] == mx);

        if (firstMin || lastMax) return 1;

        if (s[0] != mx && s[n - 1] != mn) return 2;

        if (s[0] == mx && s[n - 1] == mn) {
            for (int i = 1; i < n - 1; i++) {
                if (s[i] == mn || s[i] == mx) {
                    return 2;
                }
            }
            return 3;
        }

        return 2;
    }
};
