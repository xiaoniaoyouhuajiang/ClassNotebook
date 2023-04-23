# Task
[Link](https://leetcode.com/problems/number-of-islands/description/)

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:
```
11110
11010
11000
00000
```
Answer: 1


Example 2:
```
11000
11000
00100
00011
```
Answer: 3

# Solutions
* Depth-first searrch
* Breadth-first search
* Maintaining which cell belongs to which island with a disjoint-set-union data structure
* Ad-hoc solutions:
Set islandId to each cell according to a simple rule: we are moving from left to right, from top to bottom, and 
- we label the cell with new islandId if left and upper cells are water, 
- we label the cell like left cell if upper cell is water and left cell is ground
- we label the cell like upper cell if upper cell is ground, even if left cell is ground with different islandId. 
This can lead to mistakes in labeling, so we can have different cells of one island labeled with different ids.
To correct these mistakes, we will save pairs (left cell's id, upper cell's id) if left cell's id != upper cell's id and we will consider these pairs as edges in graph where every islandId is a vertex. 
Then the task will be solved if we count connected components of this graph.

Assume all cells could be island. We move from top to the bootom from  left to the right 
so possible lends in island can be only either on the left or on the right or on the bottom side of each cells
we don`t need to check upper neighbor of the land. All visited land cells willl be placed in vector visitedElements.

# Other remarks
* Some used mutability of the array and sunk the islands on the go, instead of coloring them