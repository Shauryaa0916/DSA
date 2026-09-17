class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        vector<int> best(n, INF);

        unordered_map<int, int> mp;
        mp[0] = -1;

        int sum = 0;
        int ans = INF;
        int minLen = INF;

        for (int i = 0; i < n; i++) {
            sum += arr[i];

            // Check if a subarray ending at i has sum = target
            if (mp.find(sum - target) != mp.end()) {
                int start = mp[sum - target];
                int len = i - start;

                // If there is a previous non-overlapping subarray
                if (start >= 0 && best[start] != INF) {
                    ans = min(ans, best[start] + len);
                } 
                else if (start == 0) {
                    // No previous subarray
                }
            }

            // Store the minimum length subarray ending at or before i
            if (i > 0)
                best[i] = best[i - 1];

            if (mp.find(sum - target) != mp.end()) {
                int start = mp[sum - target];
                int len = i - start;

                best[i] = min(best[i], len);
            }

            mp[sum] = i;
        }

        return ans == INF ? -1 : ans;
    }
};