typedef pair<TreeNode*, int> nodeDepth;

class Solution
{
public:
    vector<int> largestValues(TreeNode* root)
	{
        vector<int> maxValues;
		if (root == NULL) return maxValues;

		stack<nodeDepth> tree;
		tree.push(nodeDepth(root, 0));
		while (!tree.empty())
		{
			nodeDepth node = tree.top();
			tree.pop();

			unsigned int depth = node.second;
			if (maxValues.size() < depth + 1)
				maxValues.push_back(node.first->val); // new level of depth
			else
				maxValues[depth] = std::max(maxValues[depth], node.first->val);

			// consider left and right childs
			if (node.first->left != NULL) tree.push(nodeDepth(node.first->left, depth + 1));
			if (node.first->right != NULL) tree.push(nodeDepth(node.first->right, depth + 1));
		}

		return maxValues;
    }
};