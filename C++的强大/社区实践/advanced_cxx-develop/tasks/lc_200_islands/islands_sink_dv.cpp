class Solution {
public:
  int numIslands(vector<vector<char>>& grid) {
    int islands = 0;
    function<int(int, int)> sink = [&sink, &grid](int i, int j) {
      if ((i >= 0) && (i < grid.size()) && (j >= 0) && (j < grid[0].size()) && (grid[i][j] == '1')) {
	grid[i][j] = '0';
	sink(i + 1, j);
	sink(i - 1, j);
	sink(i, j + 1);
	sink(i, j - 1);
	return 1;
      }
      return 0;
    };
    for (int i = 0; i < grid.size(); i++)
      for (int j = 0; j < grid[0].size(); j++)
	islands += sink(i, j);
    return islands;
  }
};
