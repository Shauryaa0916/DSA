#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<string>& grid, int energy) {
        int m = grid.size();
        int n = grid[0].size();

        int sr = -1, sc = -1;
        vector<pair<int, int>> litter;

        // Find S and all L
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (grid[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        // No litter
        if (k == 0) return 0;

        // Give each litter cell a bit number
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            auto [r, c] = litter[i];
            litterId[r][c] = i;
        }

        int fullMask = (1 << k) - 1;

        /*
            best[r][c][mask] =
            maximum energy with which we have reached
            (r,c) after collecting 'mask'.
        */
        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(n, vector<int>(1 << k, -1))
        );

        struct State {
            int r, c;
            int mask;
            int en;
            int dist;
        };

        queue<State> q;

        best[sr][sc][0] = energy;
        q.push({sr, sc, 0, energy, 0});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            State cur = q.front();
            q.pop();

            int r = cur.r;
            int c = cur.c;
            int mask = cur.mask;
            int en = cur.en;
            int dist = cur.dist;

            // All litter collected
            if (mask == fullMask) {
                return dist;
            }

            // If energy is 0, we can move only if we are on R
            if (en == 0 && grid[r][c] != 'R') {
                continue;
            }

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // Boundary check
                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                // Obstacle
                if (grid[nr][nc] == 'X')
                    continue;

                // Moving costs 1 energy
                int newEnergy = en - 1;

                // If we reach R, reset energy
                if (grid[nr][nc] == 'R') {
                    newEnergy = energy;
                }

                // Collect litter
                int newMask = mask;

                if (litterId[nr][nc] != -1) {
                    newMask |= (1 << litterId[nr][nc]);
                }

                /*
                    If we've already reached this
                    (position, mask) with >= energy,
                    this state is not useful.
                */
                if (best[nr][nc][newMask] >= newEnergy)
                    continue;

                best[nr][nc][newMask] = newEnergy;

                q.push({
                    nr,
                    nc,
                    newMask,
                    newEnergy,
                    dist + 1
                });
            }
        }

        // Impossible to collect all litter
        return -1;
    }
};