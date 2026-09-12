class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 3>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {intervals[i][0], intervals[i][1], intervals[i][2]};
        }

        // Sort by starting point, then ending point, then original index
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);

        sort(ord.begin(), ord.end(), [&](int x, int y) {
            if (intervals[x][0] != intervals[y][0])
                return intervals[x][0] < intervals[y][0];
            if (intervals[x][1] != intervals[y][1])
                return intervals[x][1] < intervals[y][1];
            return x < y;
        });

        vector<int> starts(n);
        for (int i = 0; i < n; i++)
            starts[i] = intervals[ord[i]][0];

        // next[i] = first interval whose left > current right
        vector<int> nxt(n);
        for (int i = 0; i < n; i++) {
            int r = intervals[ord[i]][1];
            nxt[i] = upper_bound(starts.begin(), starts.end(), r) - starts.begin();
        }

        // dp[pos][count] = best answer from pos onward
        // Store both score and selected original indices.
        struct State {
            long long score = 0;
            vector<int> ids;
        };

        vector<vector<State>> dp(n + 1, vector<State>(5));

        auto better = [](const State& x, const State& y) {
            if (x.score != y.score)
                return x.score > y.score;

            return x.ids < y.ids;   // lexicographically smaller
        };

        for (int i = n - 1; i >= 0; i--) {
            for (int cnt = 0; cnt <= 4; cnt++) {
                // Don't take current interval
                State best = dp[i + 1][cnt];

                // Take current interval
                if (cnt < 4) {
                    State take = dp[nxt[i]][cnt + 1];
                    take.score += intervals[ord[i]][2];
                    take.ids.push_back(ord[i]);

                    sort(take.ids.begin(), take.ids.end());

                    if (better(take, best))
                        best = take;
                }

                dp[i][cnt] = best;
            }
        }

        return dp[0][0].ids;
    }
};