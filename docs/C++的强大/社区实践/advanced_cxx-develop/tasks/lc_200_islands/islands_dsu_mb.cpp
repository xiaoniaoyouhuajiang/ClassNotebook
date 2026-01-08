#include <unordered_set>
#include <vector>
#include <cassert>
#include <algorithm>

std::vector<size_t> parent;
size_t sz;

inline size_t ix(size_t i, size_t j){return i*sz+j;}

size_t find_parent(size_t v){
  if (v == parent[v])
    return v;
  return parent[v] = find_parent(parent[v]);
};

#include <cstdlib>
void union_sets (int a, int b) {
  a = find_parent (a);
  b = find_parent (b);
  if (a == b) return;
  if(rand() & 1)
    parent[b] = a;
  else
    parent[a] = b;
};

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        using namespace std;
	if(grid.size() == 0) return 0;
        sz = grid[0].size() + 1;
	// But what if a dog ate your DFS?
	parent=vector<size_t>(grid.size() * grid[0].size());
	iota(parent.begin(), parent.end(), 0);

	parent = vector<size_t>(
				(grid.size() + 1) * (grid[0].size() + 1));
	iota(parent.begin(), parent.end(), 0);
	grid.push_back(vector<char>(grid[0].size() + 1, '0'));

	for(size_t i = 0; i < grid.size() - 1; ++i){
	  grid[i].push_back('0');
	  for(size_t j = 0; j < grid[i].size(); ++j){
	    if(grid[i][j] == '1' && grid[i + 1][j] == '1')
	      union_sets(ix(i, j), ix(i + 1 , j));
	    if(grid[i][j] == '1' && grid[i][j + 1] == '1')
	      union_sets(ix(i, j), ix(i, j + 1));
	  }
	}

	unordered_set<size_t> colors;
	for(size_t i = 0; i < grid.size() - 1; ++i)
	  for(size_t j = 0; j < grid[i].size(); ++j)
	    if(grid[i][j] == '1')
	      colors.insert(find_parent(ix(i, j)));
	// These inserts themselves take linear time by the same argument
	// as vector resizings
	return colors.size();
    }
};

#include <iostream>
int main(){
    Solution sol;
    std::vector<std::vector<char>> temp = {{'1', '0', '1'}};
    std::cout << sol.numIslands(temp) << std::endl;
    return 0;
}
