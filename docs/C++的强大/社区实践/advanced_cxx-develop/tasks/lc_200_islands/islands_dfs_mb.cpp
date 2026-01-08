#include <vector>
#include <cassert>

namespace advcxx{
    using namespace std;
  // You could typedef a color for more expressive code
    const int NO_COLOR = -1;
    int di[4] = {-1, 0, 1, 0};
    int dj[4] = {0, 1, 0, -1};
    
    void dfs(size_t i, size_t j, const vector<vector<char>>& grid,
	     vector<vector<int>>& color, int next_color){
        if(grid[i][j] != '1') return;
	// Can be used without qualifier inside  namespace
        if(color[i][j] != NO_COLOR) return;

        color[i][j] = next_color;
        for(size_t k = 0; k < 4; ++k){
            int ni = i + di[k], nj = j + dj[k];
            if(ni >= 0 && nj >= 0 && ni < grid.size() && nj < grid[i].size()){
                dfs(ni, nj, grid, color, next_color);
            }
        }
    }
}

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        using namespace std;
	if(grid.size() == 0) return 0;
	// Maintaining two arrays was rather much hassle
	// Does someone want to try struct cell{bool is_land; int color;explicit cell(char c){...}}?
        vector<vector<int>> color(grid.size(),
				  vector<int>(grid[0].size(), advcxx::NO_COLOR));
        int curr_color = 0;

        for(size_t i = 0; i < grid.size(); ++i){
            assert(color[i].size() == grid[i].size());
            for(size_t j = 0; j < grid[i].size(); ++j){
                if(grid[i][j] == '1' && color[i][j] == advcxx::NO_COLOR){
                    advcxx::dfs(i, j, grid, color, ++curr_color);
                }
            }
        }
        return curr_color;
    }
};
/*
#include <iostream>
int main(){
    Solution sol;
    std::vector<std::vector<char>> temp = {{'1', '0', '1'}};
    std::cout << sol.numIslands(temp) << std::endl;
    return 0;
}*/
