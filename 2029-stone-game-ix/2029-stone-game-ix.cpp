class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        int c0 = cnt[0];
        int c1 = cnt[1];
        int c2 = cnt[2];

        // No stones with remainder 1 or 2
        if (c1 == 0 && c2 == 0)
            return false;

        // If one of c1/c2 is zero
        if (c1 == 0 || c2 == 0) {
            int mx = max(c1, c2);
            return mx > 2 && (c0 % 2 == 1);
        }

        // Both remainder 1 and 2 stones exist
        if (c0 % 2 == 0) {
            return true;
        }

        // c0 is odd
        return abs(c1 - c2) > 2;
    }
};