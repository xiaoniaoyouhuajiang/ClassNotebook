#ifndef Command_h
#define Command_h
#include <vector>
#include "GameMaster.h"
#include <fstream>
#include <algorithm>
#include <iterator>
class Base;
class GameUnits;
class GameMap;
class TeamEntity;
//class FriendsEntity;
//class EnemiesEntity;
class Unit;
class GameMaster;
class Memento;

class Command{
public:
    virtual void execute()  = 0;
};

class BaseCommand:public Command{
public:
    Base* baseCont;
    BaseCommand(Base* base): baseCont(base){}
    ~BaseCommand();
    
};

class UnitCommand:public Command{
public:
    int cost;
    int* remainingEnergy;
    TeamEntity* unitCont;
    UnitCommand(TeamEntity* unitCont, int* remainingEnergy): unitCont(unitCont), remainingEnergy(remainingEnergy), cost(1){}
    ~UnitCommand();
};

class HelpCommand:public Command{
public:
    void execute()  override;
};

class SwitchUnitCommand: public Command{
public:
    
    int* index;
    TeamEntity* unitCont; //GameU
    SwitchUnitCommand(TeamEntity* unitCont, int* index):unitCont(unitCont), index(index){}
    ~SwitchUnitCommand();
    void execute() override;

};

class SaveLoadCommand: public Command{
public:
    GameMaster::Memento* memento;
    std::string fileName;
    SaveLoadCommand(GameMaster::Memento* mori):memento(mori), fileName("SaveForGame.txt"){};
    ~SaveLoadCommand();
};
//-------------------------------------//

//---------------------UnitCommand----------------------//
class MoveCommand: public UnitCommand{
public:
    int x;
    int y;
    int index;
    bool* death;
    GameMap *map;
    MoveCommand(int x, int y, int index, GameMap* map, TeamEntity* unitCont, bool* death, int* remainingEnergy):UnitCommand(unitCont, remainingEnergy), x(x), y(y), index(index), map(map), death(death){}
    ~MoveCommand();
    void execute()  override;

};

class AttackCommand: public UnitCommand{
public:
    GameMap* map;
    std::vector <TeamEntity*> enemiesV;
    int index;
    AttackCommand(GameMap* map, std::vector<TeamEntity*> enemies, TeamEntity* unitCont, int index, int* remainingEnergy):UnitCommand(unitCont, remainingEnergy), map(map), index(index){
        for(auto it = enemies.begin(); it != enemies.end(); it++){
            enemiesV.push_back(*it);
        }
    }
    
    ~AttackCommand();
    void execute()  override;

};
//---------------------BaseCommand----------------------//

class CreateUnitInBaseCommand: public BaseCommand{
public:
    int cost;
    int* remainingEnergy;
    CreateUnitInBaseCommand(Base* base,  int* remainingEnergy):BaseCommand(base),remainingEnergy(remainingEnergy),cost(2) {}
    void execute()  override;

};

class SelectUnitInBaseCommand: public BaseCommand{
public:
    
    TeamEntity* unitCont;
    Unit* newUnit;
    GameMap *map;

    SelectUnitInBaseCommand(TeamEntity* unitCont, Base* base, GameMap *map):BaseCommand(base), unitCont(unitCont), map(map){}
    ~SelectUnitInBaseCommand();
    void execute()  override;

};


class BaseStatCommand: public BaseCommand{
    public:
        BaseStatCommand(Base* base):BaseCommand(base){};
        void execute()  override;

};


//---------------------SaveLoadCommand----------------------//

class SaveFCommand: public SaveLoadCommand{
private:
    std::ofstream saveFile;
public:
    SaveFCommand(GameMaster::Memento* memento);
    ~SaveFCommand();
    void execute()  override;
    
    
};

class LoadFCommand: public SaveLoadCommand{
private:
    std::ifstream saveFile;
    GameMaster* gm;
public:
    LoadFCommand(GameMaster::Memento* memento, GameMaster* gm);
    ~LoadFCommand();
    void execute()  override;
};

#endif /* Command_h */
