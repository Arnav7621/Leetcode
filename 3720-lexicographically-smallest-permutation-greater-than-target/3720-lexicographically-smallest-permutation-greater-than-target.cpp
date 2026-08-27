class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        int baseCnt[26] = {0};
        for (char c : s) baseCnt[c - 'a']++;
        
        // Step 1: find the largest valid divergence index bestI
        int cnt[26];
        memcpy(cnt, baseCnt, sizeof(baseCnt));
        int bestI = -1;
        
        for (int i = 0; i < n; i++) {
            // check if some char > target[i] exists in current cnt
            bool found = false;
            for (int c = target[i] - 'a' + 1; c < 26; c++) {
                if (cnt[c] > 0) { found = true; break; }
            }
            if (found) bestI = i;
            
            // try to consume target[i] to extend exact-match prefix
            int idx = target[i] - 'a';
            if (cnt[idx] > 0) {
                cnt[idx]--;
            } else {
                break; // prefix can't extend further
            }
        }
        
        if (bestI == -1) return "";
        
        // Step 2: rebuild counts after removing target[0..bestI-1]
        int cnt2[26];
        memcpy(cnt2, baseCnt, sizeof(baseCnt));
        for (int i = 0; i < bestI; i++) {
            cnt2[target[i] - 'a']--;
        }
        
        // pick smallest char > target[bestI]
        int chosen = -1;
        for (int c = target[bestI] - 'a' + 1; c < 26; c++) {
            if (cnt2[c] > 0) { chosen = c; break; }
        }
        cnt2[chosen]--;
        
        // build result
        string result = target.substr(0, bestI);
        result += char('a' + chosen);
        for (int c = 0; c < 26; c++) {
            for (int k = 0; k < cnt2[c]; k++) {
                result += char('a' + c);
            }
        }
        
        return result;
    }
};