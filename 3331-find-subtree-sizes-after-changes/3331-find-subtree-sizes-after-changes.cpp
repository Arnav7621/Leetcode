
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n), tree(n);
        vector<int> p = parent, ans(n, 1), last(26, -1);

        for (int i = 1; i < n; i++)
            adj[parent[i]].push_back(i);

        function<void(int)> dfs = [&](int u) {
            int c = s[u] - 'a';
            int prev = last[c];

            if (prev != -1) p[u] = prev;

            last[c] = u;

            for (int v : adj[u])
                dfs(v);

            last[c] = prev;
        };

        dfs(0);

        for (int i = 1; i < n; i++)
            tree[p[i]].push_back(i);

        function<int(int)> calc = [&](int u) {
            for (int v : tree[u])
                ans[u] += calc(v);
            return ans[u];
        };

        calc(0);
        return ans;
    }
};
