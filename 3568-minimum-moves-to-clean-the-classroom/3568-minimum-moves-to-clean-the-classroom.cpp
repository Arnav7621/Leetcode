class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {

        int m = classroom.size();
        int n = classroom[0].size();

        int sr, sc;
        vector<pair<int,int>> litter;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {

                if(classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }

                if(classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        if(k == 0)
            return 0;

        vector<vector<int>> id(m, vector<int>(n, -1));

        for(int i = 0; i < k; i++)
            id[litter[i].first][litter[i].second] = i;

        int full = (1 << k) - 1;

        // best[r][c][mask] = maximum energy we've had
        vector<vector<vector<int>>> best(
            m, vector<vector<int>>(n, vector<int>(1 << k, -1))
        );

        queue<array<int,4>> q;

        q.push({sr, sc, energy, 0});
        best[sr][sc][0] = energy;

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        int moves = 0;

        while(!q.empty()) {

            int sz = q.size();

            while(sz--) {

                auto cur = q.front();
                q.pop();

                int r = cur[0];
                int c = cur[1];
                int e = cur[2];
                int mask = cur[3];

                if(mask == full)
                    return moves;

                if(e == 0)
                    continue;

                for(int d = 0; d < 4; d++) {

                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if(nr < 0 || nr >= m ||
                       nc < 0 || nc >= n ||
                       classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    // Collect litter
                    if(classroom[nr][nc] == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    // Reset energy
                    if(classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    // If we've already reached this state with
                    // equal or more energy, this state is useless.
                    if(ne <= best[nr][nc][nmask])
                        continue;

                    best[nr][nc][nmask] = ne;

                    q.push({nr, nc, ne, nmask});
                }
            }

            moves++;
        }

        return -1;
    }
};