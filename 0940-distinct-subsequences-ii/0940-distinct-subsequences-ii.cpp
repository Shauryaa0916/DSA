class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;

        vector<long long> end(26, 0);
        long long total = 0;

        for (char ch : s) {
            int i = ch - 'a';

            long long newSubseq = (total + 1) % MOD;

            total = (total - end[i] + newSubseq + MOD) % MOD;

            end[i] = newSubseq;
        }

        return total;
    }
};