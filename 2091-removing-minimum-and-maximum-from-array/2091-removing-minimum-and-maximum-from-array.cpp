class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int mn = INT_MAX, mx = INT_MIN;
        int minIndex = -1, maxIndex = -1;

        // Find minimum and maximum with their indices
        for (int i = 0; i < n; i++) {
            if (nums[i] < mn) {
                mn = nums[i];
                minIndex = i;
            }

            if (nums[i] > mx) {
                mx = nums[i];
                maxIndex = i;
            }
        }

        // Make sure minIndex comes before maxIndex
        if (minIndex > maxIndex)
            swap(minIndex, maxIndex);

        // 3 possibilities:
        // 1. Remove both from front
        int front = maxIndex + 1;

        // 2. Remove both from back
        int back = n - minIndex;

        // 3. Remove min from front and max from back
        int both = (minIndex + 1) + (n - maxIndex);

        return min({front, back, both});
    }
};