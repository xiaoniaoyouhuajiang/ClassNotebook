/*
Description: we asume all cells could be island. We move from top to the bootom from  left to the right 
so possible lends in island can be only either on the left or on the right or on the bottom side of each cells
we don`t need to check upper neighbor of the land. All visited lends willl be placed in vector visitedElements 
*/
#include <vector>
class Solution{
public:
	int numIslands(vector< vector<char> >& grid) {
		int count = 0;
		int numLine = grid.size();
		int numCall = grid[0].size();
		vector<vector<int> > visitedElemets;

		for(int i=0; i < numLine; i++)
		{
			for(int j=0; j < numCall; j++)
			{
				if(grid[i][j]=='1')
				{
					if(!isElement(i,j,visitedElemets))
					{
						count++;
						visitAllConnectedLands(i,j,grid,visitedElemets);
					}
				}
			}
		}

		return count;
    }

    bool isElement(int i,int j, vector<vector<int> >& vE)
    {
		for(int k=0;k<vE.size();k++)
		{
			if(i==vE[k][0] && j==vE[k][1])
				return true;
		}
		return false;
	}

    void visitAllConnectedLands(int i, int j, vector< vector<char> >& grid, vector<vector<int> >& vE)
    {
	int numLine = grid.size();
	int numCall = grid[0].size();

	vector<int> v(2);
	v[0]=i; v[1]=j;

	if(grid[i][j]=='1' && !isElement(i,j,vE))
	{
		//indicate that this elemen was visited
		vE.push_back(v);

		if(j > 0)
		{
			visitAllConnectedLands(i, j-1, grid, vE);
		}
		if(j < (numCall - 1))
		{
			visitAllConnectedLands(i, j+1, grid, vE);
		}

		if(i < (numLine - 1))
		{
			visitAllConnectedLands(i+1, j, grid, vE);
		}
	}
    }
};
