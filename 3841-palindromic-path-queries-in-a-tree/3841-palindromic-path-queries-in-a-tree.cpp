class Solution {
public:
    vector<int> bit;
    int N;

    void upd(int i, int v) {          // i is 0-indexed
        for (i++; i <= N; i += i & -i) bit[i] ^= v;
    }
    int pre(int i) {                  // XOR of positions [0, i]
        int r = 0;
        for (i++; i > 0; i -= i & -i) r ^= bit[i];
        return r;
    }
    int range(int l, int r) {
        return pre(r) ^ (l ? pre(l - 1) : 0);
    }

    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        N = n;
        bit.assign(n + 1, 0);
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> parent(n, -1), depth(n, 0), sz(n, 1), heavy(n, -1), head(n), pos(n);

        // BFS order to compute parent/depth, then sizes in reverse
        vector<int> order;
        order.reserve(n);
        order.push_back(0);
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v != parent[u]) {
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    order.push_back(v);
                }
            }
        }
        for (int i = n - 1; i > 0; i--) {
            int u = order[i];
            sz[parent[u]] += sz[u];
        }
        for (int u : order) {
            int best = -1;
            for (int v : adj[u]) {
                if (v != parent[u] && (best == -1 || sz[v] > sz[best])) best = v;
            }
            heavy[u] = best;
        }

        // Assign head and positions: each chain gets contiguous positions
        int cur = 0;
        for (int u : order) {
            if (u == 0 || heavy[parent[u]] != u) {
                for (int v = u; v != -1; v = heavy[v]) {
                    head[v] = u;
                    pos[v] = cur++;
                }
            }
        }

        for (int i = 0; i < n; i++) upd(pos[i], 1 << (s[i] - 'a'));

        vector<bool> ans;
        for (auto& q : queries) {
            if (q[0] == 'u') {
                int u;
                char c;
                sscanf(q.c_str(), "update %d %c", &u, &c);
                int diff = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                s[u] = c;
                upd(pos[u], diff);
            } else {
                int u, v;
                sscanf(q.c_str(), "query %d %d", &u, &v);
                int x = 0;
                while (head[u] != head[v]) {
                    if (depth[head[u]] < depth[head[v]]) swap(u, v);
                    x ^= range(pos[head[u]], pos[u]);
                    u = parent[head[u]];
                }
                if (depth[u] > depth[v]) swap(u, v);
                x ^= range(pos[u], pos[v]);
                ans.push_back((x & (x - 1)) == 0);
            }
        }
        return ans;
    }
};