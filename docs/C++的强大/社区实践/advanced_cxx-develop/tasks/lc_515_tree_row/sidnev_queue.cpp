/*
  BFS-based solution. Scan every level of tree with elements from std::queue.
  DFS solution will be better for narrow trees.
*/

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> out;      
        if (root == nullptr)
            return out;
        
        queue<TreeNode*> q;        
        q.emplace(root);
        while (!q.empty()) {
            int size = q.size();            
            int max_val = q.front()->val;
            for (int i = 0; i < size; ++i) {
                auto node = q.front();
                q.pop();                                    
                max_val = max(max_val, node->val);
                
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }            
            out.emplace_back(max_val);
        }
        return out;
    }
};
