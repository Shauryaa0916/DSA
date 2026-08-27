class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        sort(s.begin(), s.end());

        // First try: permutation of s that is >= target
        string cur = s;

        // Build answer using backtracking
        function<bool(int, vector<int>&, string&)> dfs =
            [&](int pos, vector<int>& cnt, string& res) -> bool {

            if (pos == n)
                return res > target;

            int start = 0;

            // If prefix is already greater, use smallest available char
            if (res > target.substr(0, pos))
                start = 0;
            else
                start = target[pos] - 'a';

            for (int c = start; c < 26; c++) {
                if (cnt[c] == 0) continue;

                if (c < target[pos] - 'a' && res == target.substr(0, pos))
                    continue;

                cnt[c]--;
                res.push_back('a' + c);

                if (dfs(pos + 1, cnt, res))
                    return true;

                res.pop_back();
                cnt[c]++;
            }

            return false;
        };

        vector<int> cnt(26, 0);
        for (char c : s)
            cnt[c - 'a']++;

        // Simpler and correct: find next permutation of target
        // using the multiset of characters from s.
        string ans = "";

        for (int i = n - 1; i >= 0; i--) {
            vector<int> f(26, 0);

            bool possible = true;

            for (int j = 0; j < i; j++) {
                f[target[j] - 'a']++;
            }

            for (int j = 0; j < 26; j++) {
                f[j] = cnt[j] - f[j];
                if (f[j] < 0)
                    possible = false;
            }

            if (!possible) continue;

            int x = target[i] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (f[c] > 0) {
                    ans = target.substr(0, i);
                    ans += char('a' + c);
                    f[c]--;

                    for (int j = 0; j < 26; j++) {
                        while (f[j] > 0) {
                            ans += char('a' + j);
                            f[j]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};