class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Total length of path = m + n - 1
        // A valid parentheses string must have even length.
        if ((m + n - 1) % 2 != 0)
            return false;

        // dp[i][j] = set of possible balance values at (i,j)
        vector<vector<bitset<101>>> dp(m, vector<bitset<101>>(n));

        // Starting cell must be '('
        if (grid[0][0] == ')')
            return false;

        dp[0][0][1] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                if (grid[i][j] == '(') {
                    if (i > 0)
                        dp[i][j] |= (dp[i - 1][j] << 1);

                    if (j > 0)
                        dp[i][j] |= (dp[i][j - 1] << 1);
                } 
                else {
                    if (i > 0)
                        dp[i][j] |= (dp[i - 1][j] >> 1);

                    if (j > 0)
                        dp[i][j] |= (dp[i][j - 1] >> 1);
                }

                // Negative balance is automatically discarded.
            }
        }

        // For a valid parentheses string, final balance must be 0.
        return dp[m - 1][n - 1][0];
    }
};