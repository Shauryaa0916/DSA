class Solution {
public:
    int count = 0;

    pair<long long, int> dfs(TreeNode* root) {
        if (root == nullptr)
            return {0, 0};

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        long long sum = left.first + right.first + root->val;
        int nodes = left.second + right.second + 1;

        if (root->val == sum / nodes)
            count++;

        return {sum, nodes};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return count;
    }
};