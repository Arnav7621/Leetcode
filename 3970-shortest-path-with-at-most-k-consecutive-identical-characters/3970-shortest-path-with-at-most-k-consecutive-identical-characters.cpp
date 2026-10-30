
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int,int>>> adj(n);

        for (auto &e : edges)
            adj[e[0]].push_back({e[1], e[2]});

        // dist[node][count]
        vector<vector<int>> dist(n, vector<int>(k + 1, INT_MAX));

        // {distance, node, count}
        priority_queue<tuple<int,int,int>,
            vector<tuple<int,int,int>>,
            greater<tuple<int,int,int>>> pq;

        int start = 1;
        if (start > k) return -1;

        dist[0][start] = 0;
        pq.push({0, 0, start});

        while (!pq.empty()) {
            auto [d, u, cnt] = pq.top();
            pq.pop();

            if (d != dist[u][cnt]) continue;

            if (u == n - 1) return d;

            for (auto [v, w] : adj[u]) {
                int newCnt;

                if (labels[u] == labels[v])
                    newCnt = cnt + 1;
                else
                    newCnt = 1;

                if (newCnt > k) continue;

                if (d + w < dist[v][newCnt]) {
                    dist[v][newCnt] = d + w;
                    pq.push({d + w, v, newCnt});
                }
            }
        }

        return -1;
    }
};
