class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        queue<pair<TreeNode*, std::size_t>> queue{};
        queue.emplace(root, 0);
        vector<int> result{};
        while (!queue.empty())
        {
            auto& element = queue.front();
            auto next = element.first;
            auto depth(element.second);
            if (next != nullptr)
            {
                auto nextValue(next->val);
                if (depth == result.size())
                {
                    result.push_back(nextValue);
                }
                else
                {
                    auto& value = result[depth];
                    if (nextValue > value)
                    {
                        value = nextValue;
                    }
                }
                queue.emplace(next->left, depth + 1);
                queue.emplace(next->right, depth + 1);
            }
            queue.pop();
        }
        return result;
    }
};
