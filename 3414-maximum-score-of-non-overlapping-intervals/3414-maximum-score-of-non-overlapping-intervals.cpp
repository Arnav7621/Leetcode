class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> ids;
    };

    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;
        return a.ids < b.ids;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long,4>> arr(n);

        for (int i = 0; i < n; i++) {
            arr[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        sort(arr.begin(), arr.end(), [](auto& a, auto& b) {
            if (a[0] == b[0]) return a[1] < b[1];
            return a[0] < b[0];
        });

        vector<long long> starts(n);
        for (int i = 0; i < n; i++)
            starts[i] = arr[i][0];

        vector<int> nxt(n);

        for (int i = 0; i < n; i++) {
            nxt[i] = upper_bound(starts.begin(), starts.end(), arr[i][1]) - starts.begin();
        }

        vector<array<State,5>> dp(n + 1);

        for (int i = n - 1; i >= 0; i--) {

            dp[i][0] = State();

            for (int k = 1; k <= 4; k++) {

                // Skip current interval
                State best = dp[i + 1][k];

                // Take current interval
                State take = dp[nxt[i]][k - 1];
                take.score += arr[i][2];
                take.ids.push_back((int)arr[i][3]);
                sort(take.ids.begin(), take.ids.end());

                if (better(take, best))
                    best = take;

                dp[i][k] = best;
            }
        }

        return dp[0][4].ids;
    }
};