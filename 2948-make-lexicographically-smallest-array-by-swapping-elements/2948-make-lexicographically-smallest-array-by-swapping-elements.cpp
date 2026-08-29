class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        
        // Store value with its original index
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++) {
            v.push_back({nums[i], i});
        }
        
        // Sort according to values
        sort(v.begin(), v.end());
        
        int start = 0;
        
        while (start < n) {
            int end = start;
            
            // Find all elements that belong to the same swappable group
            while (end + 1 < n && v[end + 1].first - v[end].first <= limit) {
                end++;
            }
            
            // Collect original indices of this group
            vector<int> indices;
            for (int i = start; i <= end; i++) {
                indices.push_back(v[i].second);
            }
            
            // Sort indices so smallest values go to smallest positions
            sort(indices.begin(), indices.end());
            
            for (int i = 0; i < indices.size(); i++) {
                nums[indices[i]] = v[start + i].first;
            }
            
            start = end + 1;
        }
        
        return nums;
    }
};