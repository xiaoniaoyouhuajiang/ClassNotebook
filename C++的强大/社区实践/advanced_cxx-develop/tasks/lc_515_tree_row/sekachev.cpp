/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        int row = 0;
        vector<int> result;
        scan_node(root, row);
        for (auto it = max_map.begin(); it != max_map.end(); it++) {
            result.push_back(it->second);
        }
        return result;
    }
private:
    void scan_node(TreeNode* node, int row) {
        if (!node) return;
        auto it = max_map.find(row);
        if (it != max_map.end()) {
            it->second = node->val > it->second ? node->val : it->second;
        }
        else {
            max_map.insert(pair<int,int>(row, node->val));
        }
        
        scan_node(node->left, row + 1);
        scan_node(node->right, row + 1);
    }
    map<int, int> max_map;
};