class Solution {
public:
    int n, K;
    vector<vector<int>> seg;

    void mergeNode(int node) {
        for (int i = 0; i < K; i++)
            seg[node][i] = 0;

        // Products formed by taking a non-empty prefix
        // from left part
        for (int r = 0; r < K; r++) {
            seg[node][r] += seg[node * 2][r];
        }

        // Products formed by taking a prefix from right part
        // after taking the whole left part
        int leftProduct = 0;
        for (int r = 0; r < K; r++) {
            // whole-left product is stored separately as last element
        }

        // We store:
        // seg[node][r] = number of non-empty prefixes with product r
        // To merge, we need whole product of left and right.
        // So this approach needs an extra array.
    }

    vector<int> prod;

    void build(int node, int l, int r, vector<int>& nums) {
        if (l == r) {
            prod[node] = nums[l] % K;

            seg[node].assign(K, 0);
            seg[node][prod[node]] = 1;
            return;
        }

        int mid = (l + r) / 2;
        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        prod[node] = (long long)prod[node * 2] *
                     prod[node * 2 + 1] % K;

        seg[node].assign(K, 0);

        // Prefixes completely inside left child
        for (int r = 0; r < K; r++) {
            seg[node][r] += seg[node * 2][r];
        }

        // Prefixes which contain the whole left child
        // and then some prefix of right child.
        for (int r = 0; r < K; r++) {
            if (seg[node * 2 + 1][r] == 0)
                continue;

            int newRem = (long long)prod[node * 2] * r % K;
            seg[node][newRem] += seg[node * 2 + 1][r];
        }
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            prod[node] = val % K;

            fill(seg[node].begin(), seg[node].end(), 0);
            seg[node][prod[node]] = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);

        prod[node] = (long long)prod[node * 2] *
                     prod[node * 2 + 1] % K;

        fill(seg[node].begin(), seg[node].end(), 0);

        for (int r = 0; r < K; r++) {
            seg[node][r] += seg[node * 2][r];
        }

        for (int r = 0; r < K; r++) {
            int newRem = (long long)prod[node * 2] * r % K;
            seg[node][newRem] += seg[node * 2 + 1][r];
        }
    }

    // Returns information for range [ql, qr]
    pair<int, vector<int>> query(int node, int l, int r,
                                  int ql, int qr) {
        if (ql <= l && r <= qr) {
            return {prod[node], seg[node]};
        }

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(node * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(node * 2 + 1, mid + 1, r, ql, qr);

        auto left = query(node * 2, l, mid, ql, qr);
        auto right = query(node * 2 + 1, mid + 1, r, ql, qr);

        int wholeProduct =
            (long long)left.first * right.first % K;

        vector<int> cnt(K, 0);

        // Prefixes ending in left part
        for (int r = 0; r < K; r++) {
            cnt[r] += left.second[r];
        }

        // Prefixes containing all of left part
        // and then a prefix of right part
        for (int r = 0; r < K; r++) {
            int nr = (long long)left.first * r % K;
            cnt[nr] += right.second[r];
        }

        return {wholeProduct, cnt};
    }

    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        n = nums.size();
        K = k;

        seg.resize(4 * n);
        prod.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            // We keep nums[start ... n-1].
            // Every possible suffix removal corresponds
            // to choosing a non-empty prefix of this range.
            //
            // Empty suffix = whole range.
            auto res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.second[x]);
        }

        return ans;
    }
};