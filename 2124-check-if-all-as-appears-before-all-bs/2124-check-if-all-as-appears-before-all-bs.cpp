
class Solution {
public:
    bool checkString(string s) {
        bool b = false;

        for (char c : s) {
            if (c == 'b') b = true;
            if (c == 'a' && b) return false;
        }

        return true;
    }
};
