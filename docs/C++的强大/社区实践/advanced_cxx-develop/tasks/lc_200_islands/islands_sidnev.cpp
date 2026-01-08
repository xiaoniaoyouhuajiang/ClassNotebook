class Solution {
    void fill(vector<vector<char>>& grid, const int& x, const int& y) {
        const char visited_symbol = 'x';        
        int width = grid.size();        
        int height = grid[0].size();
        
        queue<pair<int,int>> q;
        q.emplace(x, y);
        
        while (!q.empty()) {
            int i = q.front().first;
            int j = q.front().second;
            q.pop();
            
            if (grid[i][j] != visited_symbol) {            
                grid[i][j] = visited_symbol;

                if (i + 1 < width && grid[i + 1][j] == '1')
                    q.emplace(i + 1, j);
                if (j + 1 < height && grid[i][j + 1] == '1')
                    q.emplace(i, j + 1);
                if (i - 1 >= 0 && grid[i - 1][j] == '1')
                    q.emplace(i - 1, j);
                if (j - 1 >= 0 && grid[i][j - 1] == '1')
                    q.emplace(i, j - 1);
            }
        }
    }
    
public:
    int numIslands(vector<vector<char>>& grid) {
        
        auto width = grid.size();        
        if (width == 0)
            return 0;
        auto height = grid[0].size();
        int count = 0;
        
        for (size_t i = 0; i < width; ++i) {
            for (size_t j = 0; j < height; ++j) {
                if (grid[i][j] == '1') {
                    fill(grid, i, j);
                    ++count;
                }
            }
        }
        
        return count;
    }
};

