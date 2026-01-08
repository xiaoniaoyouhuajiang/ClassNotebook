class Solution {
public:
	vector<int> largestValues(TreeNode* root) {
		vector<int> result;
		if (root != nullptr) {
			result.push_back(root->val);

			queue<pair<TreeNode*, size_t>> q;
			q.emplace(root, 0);

			while (!q.empty()) {
				TreeNode* node = q.front().first;

				int val = node->val;
				TreeNode* left = node->left;
				TreeNode* right = node->right;

				size_t level = q.front().second;

				q.pop();

				if (result.size() == level)
					result.push_back(val);
				else if (result[level] < val)
					result[level] = val;

				++level;

				if (left != nullptr)
					q.emplace(left, level);
				if (right != nullptr)
					q.emplace(right, level);
			}
		}
		return result;
	}
};
