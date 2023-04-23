

#ifndef GameMaster_h
#define GameMaster_h
#include <vector>
#include "Base.h" //WTF
class GameMap;
class Unit;
class Base;


class GameUnits{ 
public:
    
    int size;
    std::vector <Unit*> units;
    GameUnits();
    bool moveUnit(int x, int y, int index, GameMap &gameMap);
    Unit* getUnit(int x, int y);
    void addUnit(Unit* unit, int x, int y, GameMap &map);
};


class GameMaster {
public:
    GameMap *map;
    GameUnits units;
    Base *base;
    void gameCycle();
    void setMap();
    void setBase();
    void baseControl();
    GameMaster() {
        base = nullptr;
        map = nullptr;
        gameCycle();
    }
};



#endif /* GameMaster_h */


