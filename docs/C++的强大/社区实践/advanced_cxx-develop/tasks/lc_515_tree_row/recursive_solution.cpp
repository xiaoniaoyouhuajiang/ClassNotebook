class Solution {
	void traverse(TreeNode* node, vector<int>& res, int level) {
		if (node == NULL) return;
		
		if (res.size() == level) {
			res.push_back(node->val);	
		} else {
			res[level] = std::max(res[level], node->val);
		}	

		traverse(node->left, res, level + 1);
		traverse(node->right, res, level + 1);
	}
public:
	vector<int> largestValues(TreeNode* root) {
    		vector<int> res(0);
        		traverse(root, res, 0);
        		return res;
    	}
};
