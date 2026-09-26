class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store knowledge in a map
        for (auto &x : knowledge) {
            mp[x[0]] = x[1];
        }

        string ans;
        int i = 0;

        while (i < s.length()) {

            if (s[i] == '(') {
                i++; // skip '('

                string key;

                // Extract key until ')'
                while (s[i] != ')') {
                    key += s[i];
                    i++;
                }

                // i is now at ')'
                i++; // skip ')'

                // Check if key exists
                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                } else {
                    ans += "?";
                }
            }
            else {
                // Normal character
                ans += s[i];
                i++;
            }
        }

        return ans;
    }
};