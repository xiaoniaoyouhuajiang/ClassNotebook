/*
  we go through the tree by queue to visit all node on the same level
  we will change std::vector<int> result[level] if we face bigger value on the same level
*/
#include <iostream>
#include <vector>
#include <queue>

//structure for level remembering
struct NodeLevel{
 	int level;
 	TreeNode* node;
};
class Solution {
public:
	std::vector<int> result;
	std::queue<NodeLevel> nodeQueue;
    std::vector<int> largestValues(TreeNode* root) {
    	largestValuesWithLevel(root,0);
    	return result;
    }
    void largestValuesWithLevel(TreeNode* node,int level)
    {
    	if(level == result.size())
    	{
    		result.push_back(node->val);
    	}
    	if((result.size() - 1) == level)
    	{
    		if(node->val > result[level])
    			result[level] = node->val; 
    	}
    	if(node->left != NULL)
    	{
    		NodeLevel nd;
    		nd.level = level + 1;
    		nd.node = node->left;
    		nodeQueue.push(nd);
    	}
    	if(node->right != NULL)
    	{
    		NodeLevel nd;
    		nd.level = level + 1;
    		nd.node = node->right;
    		nodeQueue.push(nd);
    	}
    	while(!nodeQueue.empty())
    	{
    		TreeNode* nextNode = nodeQueue.front().node;
    		int nextLevel = nodeQueue.front().level;
    		nodeQueue.pop();
    		largestValuesWithLevel(nextNode,nextLevel);	
    	}
    }
};
