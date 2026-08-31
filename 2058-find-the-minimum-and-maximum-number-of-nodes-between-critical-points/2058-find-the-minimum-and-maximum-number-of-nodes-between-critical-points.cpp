class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> ans = {-1, -1};

        ListNode* prev = head;
        ListNode* curr = head->next;

        int pos = 1;
        int first = -1;
        int last = -1;

        int minDist = INT_MAX;
        int maxDist = 0;

        while (curr->next != nullptr) {
            ListNode* next = curr->next;

            // Check local maxima or local minima
            bool critical = (curr->val > prev->val && curr->val > next->val) ||
                            (curr->val < prev->val && curr->val < next->val);

            if (critical) {
                if (first == -1) {
                    // First critical point
                    first = pos;
                } else {
                    // Distance from previous critical point
                    int dist = pos - last;

                    minDist = min(minDist, dist);
                    maxDist = pos - first;
                }

                last = pos;
            }

            prev = curr;
            curr = next;
            pos++;
        }

        if (first == -1 || first == last)
            return {-1, -1};

        return {minDist, maxDist};
    }
};