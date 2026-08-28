class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        int cnt[26] = {0};
        for (char c : s) cnt[c - 'a']++;
        
        int oddCount = 0, oddChar = -1;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 1) {
                oddCount++;
                oddChar = i;
            }
        }
        
        if (n % 2 == 0 && oddCount > 0) return "";
        if (n % 2 == 1 && oddCount != 1) return "";
        
        int half[26];
        for (int i = 0; i < 26; i++) half[i] = cnt[i] / 2;
        int halfLen = n / 2;
        
        string best = "";
        
        // Case A: exact match of first half with target's prefix
        {
            int cntCopy[26];
            for (int i = 0; i < 26; i++) cntCopy[i] = half[i];
            bool possible = true;
            string hEqual(halfLen, ' ');
            for (int i = 0; i < halfLen; i++) {
                char c = target[i];
                if (cntCopy[c - 'a'] > 0) {
                    cntCopy[c - 'a']--;
                    hEqual[i] = c;
                } else {
                    possible = false;
                    break;
                }
            }
            
            if (possible) {
                string full;
                if (n % 2 == 1) {
                    char mid = (char)('a' + oddChar);
                    string secondHalf = hEqual;
                    reverse(secondHalf.begin(), secondHalf.end());
                    full = hEqual + mid + secondHalf;
                } else {
                    string secondHalf = hEqual;
                    reverse(secondHalf.begin(), secondHalf.end());
                    full = hEqual + secondHalf;
                }
                if (full > target) {
                    if (best == "" || full < best) best = full;
                }
            }
        }
        
        // Case B: deviate at position p (largest p first, matching prefix, pick smallest char > target[p], fill rest smallest)
        for (int p = halfLen - 1; p >= 0; p--) {
            int cntB[26];
            for (int i = 0; i < 26; i++) cntB[i] = half[i];
            bool prefixOk = true;
            string hB(halfLen, ' ');
            for (int i = 0; i < p; i++) {
                char c = target[i];
                if (cntB[c - 'a'] > 0) {
                    cntB[c - 'a']--;
                    hB[i] = c;
                } else {
                    prefixOk = false;
                    break;
                }
            }
            if (!prefixOk) continue;
            
            char tc = target[p];
            int chosen = -1;
            for (int c = tc - 'a' + 1; c < 26; c++) {
                if (cntB[c] > 0) {
                    chosen = c;
                    break;
                }
            }
            if (chosen == -1) continue;
            
            cntB[chosen]--;
            hB[p] = (char)('a' + chosen);
            
            for (int i = p + 1; i < halfLen; i++) {
                for (int c = 0; c < 26; c++) {
                    if (cntB[c] > 0) {
                        hB[i] = (char)('a' + c);
                        cntB[c]--;
                        break;
                    }
                }
            }
            
            string full;
            if (n % 2 == 1) {
                char mid = (char)('a' + oddChar);
                string secondHalf = hB;
                reverse(secondHalf.begin(), secondHalf.end());
                full = hB + mid + secondHalf;
            } else {
                string secondHalf = hB;
                reverse(secondHalf.begin(), secondHalf.end());
                full = hB + secondHalf;
            }
            
            if (best == "" || full < best) {
                best = full;
            }
        }
        
        return best;
    }
};