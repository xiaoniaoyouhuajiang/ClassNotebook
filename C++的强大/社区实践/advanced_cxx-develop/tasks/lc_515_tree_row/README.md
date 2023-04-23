# Task
[Link](https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/)

You need to find the largest value in each row of a binary tree.

Example:
```
Input:
          1
         / \
        3   2
       / \   \  
      5   3   9

Output: [1, 3, 9]
```

# Solutions
* Depth-first or Breadth-first search: O(n) - complexity, O(h) - memory if using stack or queue
* [DFS using std::stack solution](https://github.com/UNN-VMK-Software/advanced_cxx/blob/develop/tasks/lc_515_tree_row/std_stack_sokolov.cpp)
* [BFS using std::queue solution](https://github.com/UNN-VMK-Software/advanced_cxx/blob/develop/tasks/lc_515_tree_row/sidnev_queue.cpp)
* [Solution with std::map](https://github.com/UNN-VMK-Software/advanced_cxx/blob/develop/tasks/lc_515_tree_row/sekachev.cpp)
