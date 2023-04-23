
#ifndef Map_h
#define Map_h
#include <vector>
#include <fstream>
class GameBlock;

class GameMap{
    
public:
    int height, width;
    std::vector< std::vector<GameBlock> > map;
    

    GameMap();
    GameMap(int height, int width);
    ~GameMap();
    int getHeight();
    int getWidth();
    GameBlock* getBlock(int y, int x);
    friend std::ostream& operator <<(std::ostream& os, const GameMap& map);
    
    friend std::istream& operator >>(std::istream& os, GameMap& map);
    
};



#endif /* Map_h */
