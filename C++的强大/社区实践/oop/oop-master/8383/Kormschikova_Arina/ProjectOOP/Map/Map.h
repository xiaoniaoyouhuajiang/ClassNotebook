
#ifndef Map_h
#define Map_h

class GameBlock;

class GameMap{
    
public:
    int height, width;
    GameBlock** map;
    

    GameMap();
    GameMap(int height, int width);
    ~GameMap();
    int getHeight();
    int getWidth();
    GameBlock* getBlock(int y, int x);
};



#endif /* Map_h */
