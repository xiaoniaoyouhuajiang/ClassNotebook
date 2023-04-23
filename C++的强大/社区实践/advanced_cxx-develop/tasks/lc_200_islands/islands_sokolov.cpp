class Solution {
public:
	void visitNeigbours(const vector<vector<char> > & grid, int x0, int y0, vector<vector<char> >& islands)
	{
		int nY = islands.size() - 1;
		int nX = islands[0].size() - 1;

		if (!(x0 <= nX && x0 >= 0 && y0 <= nY && y0 >= 0 && grid[y0][x0] == '1')) return;// it is not a part of island
		if (islands[y0][x0] == '1') return; // if we visit this island
		islands[y0][x0] = '1'; // mark this cell as a visited one

		visitNeigbours(grid, x0 + 1, y0, islands);
		visitNeigbours(grid, x0 - 1, y0, islands);
		visitNeigbours(grid, x0, y0 + 1, islands);
		visitNeigbours(grid, x0, y0 - 1, islands);
	}

    int numIslands(vector<vector<char> >& grid)
	{
		if ((grid.size()) == 0) return 0;

		// Prepare data structure for marking visited islands
		vector<vector<char> > islands(grid.size());
		for (unsigned int i = 0; i < grid.size(); i++)
			islands[i].resize(grid[i].size(), '0');

		int nY = islands.size() - 1;
		int nX = islands[0].size() - 1;

		int numOfIslands = 0;
		for (int y = 0; y <= nY; y++)
		{
			for (int x = 0; x <= nX; x++)
			{
				if (grid[y][x]=='1' && islands[y][x]=='0')
				{
					numOfIslands++;
					visitNeigbours(grid, x, y, islands);
				}
			}
		}

		return numOfIslands;
    }
};
