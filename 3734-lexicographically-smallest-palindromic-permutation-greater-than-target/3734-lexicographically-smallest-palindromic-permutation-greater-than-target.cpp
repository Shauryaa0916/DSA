class Solution {
public:

    string makePalindrome(string left, char mid, bool hasMid) {
        string ans = left;

        if (hasMid)
            ans += mid;

        for (int i = left.size() - 1; i >= 0; i--)
            ans += left[i];

        return ans;
    }

    string getNext(string targetHalf, vector<int> cnt) {

        int m = targetHalf.size();

        // First try to construct targetHalf itself.
        // If impossible, find the first position where
        // we can make it bigger.
        for (int i = 0; i < m; i++) {

            // Remove targetHalf[0 ... i-1]
            if (cnt[targetHalf[i] - 'a'] == 0) {

                // At this position we cannot keep the same character.
                // Try a bigger character here.
                for (int c = targetHalf[i] - 'a' + 1; c < 26; c++) {

                    if (cnt[c] == 0)
                        continue;

                    string res = targetHalf.substr(0, i);
                    res += char('a' + c);

                    vector<int> temp = cnt;
                    temp[c]--;

                    for (int x = 0; x < 26; x++) {
                        while (temp[x] > 0) {
                            res += char('a' + x);
                            temp[x]--;
                        }
                    }

                    return res;
                }

                // No bigger character possible here
                break;
            }

            cnt[targetHalf[i] - 'a']--;
        }

        // Target half was completely possible.
        // Need the next lexicographical permutation.
        cnt.assign(26, 0);

        // Rebuild counts
        // (This part is handled by the caller when targetHalf is possible,
        // so reaching here means we need a genuine next half.)

        return "";
    }

    string findNextHalf(string targetHalf, vector<int> original) {

        int m = targetHalf.size();

        // Standard "next permutation with limited characters"
        for (int i = m - 1; i >= 0; i--) {

            vector<int> cnt = original;

            // Use prefix [0 ... i-1]
            bool ok = true;

            for (int j = 0; j < i; j++) {
                int x = targetHalf[j] - 'a';

                if (cnt[x] == 0) {
                    ok = false;
                    break;
                }

                cnt[x]--;
            }

            if (!ok)
                continue;

            int cur = targetHalf[i] - 'a';

            // Find smallest character > targetHalf[i]
            for (int c = cur + 1; c < 26; c++) {

                if (cnt[c] == 0)
                    continue;

                string res = targetHalf.substr(0, i);
                res += char('a' + c);

                cnt[c]--;

                // Smallest suffix
                for (int x = 0; x < 26; x++) {
                    while (cnt[x] > 0) {
                        res += char('a' + x);
                        cnt[x]--;
                    }
                }

                return res;
            }
        }

        return "";
    }

    string lexPalindromicPermutation(string s, string target) {

        int n = s.size();
        int m = n / 2;

        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        // More than one odd frequency => impossible
        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        // Half frequencies
        vector<int> cnt(26);

        for (int i = 0; i < 26; i++)
            cnt[i] = freq[i] / 2;

        string targetHalf = target.substr(0, m);

        // Check whether targetHalf is possible
        vector<int> temp = cnt;
        bool possible = true;

        for (char c : targetHalf) {

            if (temp[c - 'a'] == 0) {
                possible = false;
                break;
            }

            temp[c - 'a']--;
        }

        // If targetHalf is possible, construct its palindrome
        if (possible) {

            string candidate =
                makePalindrome(targetHalf, mid, n % 2);

            // Need strictly greater
            if (candidate > target)
                return candidate;

            // target itself / smaller => find next half
            string next = findNextHalf(targetHalf, cnt);

            if (next.empty())
                return "";

            return makePalindrome(next, mid, n % 2);
        }

        // targetHalf impossible => find smallest valid half > targetHalf
        string next = findNextHalf(targetHalf, cnt);

        if (next.empty())
            return "";

        return makePalindrome(next, mid, n % 2);
    }
};