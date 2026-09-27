class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string curr = "";

        for (char c : s) {

            if (c == '(') {
                // Save the string before '('
                st.push(curr);
                curr = "";
            }
            else if (c == ')') {
                // Reverse the current substring
                reverse(curr.begin(), curr.end());

                // Add it to the string before '('
                curr = st.top() + curr;
                st.pop();
            }
            else {
                curr += c;
            }
        }

        return curr;
    }
};