class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        unordered_map<int, int> freq;

        int n = nums.size();

        for (int i = 0; i <= n - k; i++) {
            unordered_set<int> st;

            for (int j = i; j < i + k; j++) {
                st.insert(nums[j]);
            }

            for (int x : st) {
                freq[x]++;
            }
        }

        int ans = -1;

        for (auto &p : freq) {
            if (p.second == 1) {
                ans = max(ans, p.first);
            }
        }

        return ans;
    }
};