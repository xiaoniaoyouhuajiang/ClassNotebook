

#ifndef GameEntity_h
#define GameEntity_h
#include <vector>
#include <deque>
class GameMap;

class TeamEntity;
class NeutralObject;
class Unit;
class Base;
// добавить геймбазы гейм объекты
enum typeU{NPC = 0, PLAYER = 1};


class GameUnits{
private:
    
public:
    int size;
    typeU type;
    int currentUnit;
    std::vector <Unit*> units;
    
    GameUnits(typeU typeu);
    bool moveUnit(int x, int y, int index, GameMap &gameMap, bool* death);
    Unit* getUnit(int x, int y);
    void addUnit(Unit* unit, int x, int y, GameMap &map);
    bool attack(int index, GameMap &gameMap, std::vector<TeamEntity*> enemies);
    int changeActiveUnit();
    void moveNPC(GameMap &gameMap, std::deque<TeamEntity*> teams);
    
    virtual void update(){};
    
    Unit* loadUnit(bool isNPC, int x, int y, int HP, int MP, int MR, int arm, char type);
    Base* loadBase(int x, int y, int HP, int maxUnit, int unitInBase);
     //  friend std::ostream& operator <<(std::ostream& os, const GameUnits& cont);
};

class GameBases{
public:
    std::vector <Base*> bases;
    Base* getBase(int x, int y);
    int sizeBase;
    int currentBase;
    GameBases();
   // friend std::ostream& operator <<(std::ostream& os, const GameBases& cont);
};

class GameNeutralObjects{
public:
    std::vector <NeutralObject*> neutralObjects;
    int sizeNO;
    NeutralObject* loadNO( int x, int y, int hp, char type);
    
    GameNeutralObjects():sizeNO(0){};
    friend std::ostream& operator <<(std::ostream& os, const GameNeutralObjects& cont);
    friend std::istream& operator >>(std::istream& os, GameNeutralObjects& cont);
};

//----------------------------------------------------//
class TeamEntity: public GameUnits, public GameBases{
public:
    bool isActive;
    bool isDefeated;
    TeamEntity(typeU typeu = PLAYER):GameUnits(typeu), isActive(false), isDefeated(false){};
    void update() override;
    friend std::ostream& operator <<(std::ostream& os, const TeamEntity& cont);
    friend std::istream& operator >>(std::istream& os, TeamEntity& cont);
};
//class EnemiesEntity: public GameUnits, public GameBases{
//
//public:
//    EnemiesEntity(){
//        type = -1;
//    }
//    friend std::ostream& operator <<(std::ostream& os, const EnemiesEntity& cont);
//    friend std::istream& operator >>(std::istream& os, EnemiesEntity& cont);
//
//};
//
//class FriendsEntity: public GameUnits, public GameBases{
//
//public:
//    FriendsEntity(){
//        type = 1;
//    }
//    friend std::ostream& operator <<(std::ostream& os, const FriendsEntity& cont);
//
//    friend std::istream& operator >>(std::istream& os, FriendsEntity& cont);
//};

//---------

#endif /* GameEntity_h */
