//We set islandId to each cell according to a simple rule: we are moving from left to right, from top to bottom, and 
//- we label the cell with new islandId if left and upper cells are water, 
//- we label the cell like left cell if upper cell is water and left cell is ground
//- we label the cell like upper cell if upper cell is ground, even if left cell is ground with different islandId. 
//This can lead to mistakes in labeling, so we can have different cells of one island labeled with different ids.
//To correct these mistakes, we will save pairs (left cell's id, upper cell's id) if left cell's id != upper cell's id 
// and we will consider these pairs as edges in graph where every islandId is a vertex. 
//Then the task will be solved if we count connected components of this graph.

class Solution {
public:
    int numIslands(vector<vector<char>>& grid)
{
    if (grid.size() == 0)
        return 0;
    int m = grid.size();
    int n = grid[0].size();
    if (n == 0)
        return 0;
    vector<vector<int>> islandsIdsGrid(m, std::vector<int>(n));
    set<pair<int,int>> islandsEdgesForMistakenSplits;
    int label = 0;
    char upperChar = '0';
    for (int i = 0; i < m; i++)
    {
        char leftChar = '0';
        for (int j = 0; j < n; j++)
        {
            if(grid[i][j] == '1')
                islandsIdsGrid[i][j] = -1;
            char currentChar = grid[i][j];
            if (i > 0)
                upperChar = grid[i - 1][j];

            if (currentChar == '1' && leftChar == '0' && upperChar == '0')
            {
                label++;
                islandsIdsGrid[i][j] = label;
            }
            if (currentChar == '1' && leftChar == '1' && upperChar == '1')
            {
                islandsIdsGrid[i][j] = islandsIdsGrid[i-1][j];
                if (islandsIdsGrid[i][j] != islandsIdsGrid[i][j - 1])
                    islandsEdgesForMistakenSplits.insert(make_pair(min(islandsIdsGrid[i][j], islandsIdsGrid[i][j - 1]),max(islandsIdsGrid[i][j],islandsIdsGrid[i][j - 1])));
            }
            if (currentChar == '1' && leftChar == '0' && upperChar == '1')
            {
                islandsIdsGrid[i][j] = islandsIdsGrid[i - 1][j];
            }
            if (currentChar == '1' && leftChar == '1' && upperChar == '0')
            {
                islandsIdsGrid[i][j] = islandsIdsGrid[i][j-1];
            }
            leftChar = grid[i][j];
        }

    }
    if(islandsEdgesForMistakenSplits.size() == 0)
    {
        return label;
    }

    int*connectedComponentsMapping = new int[label+1];
    for(int i = 0; i < label+1;i++)
    {
        connectedComponentsMapping[i] = i;//idx - element, connectedComponentsMapping[element] - name of connected components that contains element
    }
    for(auto edge : islandsEdgesForMistakenSplits)
    {
        int P1 = connectedComponentsMapping[edge.first];
        int P2 = connectedComponentsMapping[edge.second];
        for(int i = 0; i < label+1; i++)
        {
            if(connectedComponentsMapping[i] == edge.first || connectedComponentsMapping[i] == edge.second)
            {
                connectedComponentsMapping[i] = min(P1,P2);//name of connected components is the smallest element from this component
            }
        };
    }
    set<int>connectedComponentsSet;
    for(int i = 1; i < label+1; i++)
    {
        connectedComponentsSet.insert(connectedComponentsMapping[i]);
    }

    return connectedComponentsSet.size();
}
};
