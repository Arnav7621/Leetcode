class Solution {
public:
    // Parse a complete expression until ',' or '}'
    set<string> parse(string &s, int &i) {
        set<string> result;
        
        // Parse the first term
        result = parseTerm(s, i);

        // Handle union: a,b,c
        while (i < s.size() && s[i] == ',') {
            i++; // skip ','
            
            set<string> next = parseTerm(s, i);
            result.insert(next.begin(), next.end());
        }

        return result;
    }

    // Parse concatenated terms
    // Example: a{b,c}d
    set<string> parseTerm(string &s, int &i) {
        set<string> result;
        result.insert("");

        while (i < s.size() && s[i] != '}' && s[i] != ',') {
            set<string> cur;

            if (s[i] == '{') {
                i++; // skip '{'
                cur = parse(s, i);
                i++; // skip '}'
            }
            else {
                // Single lowercase letter
                cur.insert(string(1, s[i]));
                i++;
            }

            // Concatenate result with cur
            set<string> temp;

            for (string a : result) {
                for (string b : cur) {
                    temp.insert(a + b);
                }
            }

            result = temp;
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;

        set<string> result = parse(expression, i);

        return vector<string>(result.begin(), result.end());
    }
};