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
        int depth = getDepth(root);
        size_t arraySize = getArraySize(depth);

        int *arrayTree = new int [arraySize];
        for (int i = 0; i < arraySize; ++i)
            arrayTree[i] = INT_MIN;

        dumpToArray(root, arrayTree);

        sortRowsInArray(arrayTree, depth);

        return getMaximumInRows(arrayTree, depth);
    }
private:
    int getDepth(TreeNode* root, int depth = 0) {
        if (root == nullptr)
            return depth - 1;
        int maxLeftDepth = getDepth(root->left, depth + 1);
        int maxRightDepth = getDepth(root->right, depth + 1);
        return (maxLeftDepth > maxRightDepth) ? maxLeftDepth : maxRightDepth;
    }
    inline size_t getArraySize(int depth) { return pow(2, depth + 1) - 1; }
    inline int arrayShift(int depth) { return pow(2, depth) - 1; }
    void dumpToArray(TreeNode *root, int *arr, int depth = 0, int nodeNum = 0) {
        if (root == nullptr)
            return;
        int index = arrayShift(depth) + nodeNum;
        arr[index] = root->val;
        dumpToArray(root->left, arr, depth + 1, nodeNum*2);
        dumpToArray(root->right, arr, depth + 1, nodeNum*2 + 1);
    }
    void sortRowsInArray(int *arr, int depth) {
        for (int i = 1; i <= depth; ++i) {
            int startIndex = arrayShift(i);
            int endIndex = arrayShift(i + 1);
            sort(arr + startIndex, arr + endIndex);
        }
    }
    vector<int> getMaximumInRows(int *arr, int depth) {
        vector<int> res;
        for (int i = 0; i <= depth; ++i) {
            int index = arrayShift(i + 1) - 1;
            res.push_back(arr[index]);
        }
        return res;
    }
};
