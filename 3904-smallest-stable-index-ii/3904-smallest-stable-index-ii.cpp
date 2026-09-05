class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        // suffixMin[i] = min(nums[i...n-1])
        vector<int> suffixMin(n);

        suffixMin[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            suffixMin[i] = min(nums[i], suffixMin[i + 1]);
        }

        // prefix maximum maintain karte hue
        int prefixMax = nums[0];

        for (int i = 0; i < n; i++) {
            prefixMax = max(prefixMax, nums[i]);

            int instability = prefixMax - suffixMin[i];

            if (instability <= k) {
                return i;
            }
        }

        return -1;
    }
};