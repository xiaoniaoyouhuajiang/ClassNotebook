
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
    vector<int>result;
    queue<TreeNode*> currentLevel;//current tree row
    queue<TreeNode*> nextLevel;//next tree row (children)
    if (root == NULL)
        return result;
    currentLevel.push(root);
    while (!currentLevel.empty())
    {
        nextLevel = queue<TreeNode*>();
        int max = std::numeric_limits<int>::min();
        while (!currentLevel.empty())
        {
            TreeNode* node = currentLevel.front();
            currentLevel.pop();
            if (node->val >= max)
                max = node->val;
            if (node->left != NULL)
                nextLevel.push(node->left);
            if (node->right != NULL)
                nextLevel.push(node->right);
        }
        currentLevel = nextLevel;
        result.push_back(max);
    }
    return result;
}
};
