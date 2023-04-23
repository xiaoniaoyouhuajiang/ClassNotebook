

#ifndef GameMaster_h
#define GameMaster_h
#include <vector>
#include <deque>

class GameMap;
class GameNeutralObjects;
class TeamEntity;
class Command;
class Handler;
class LogProxy;
class Memento;
class GameVisualization;


enum setLog {BASES, UNITS, NOBJ, FORALL};
enum cycleEnd {NEXT = 1, EXIT = 0};
class GameMaster {
    
protected:
    
public:
    GameMaster();
    GameMap* map;
    
   
    
    std::deque<TeamEntity*> teams;
    int countTeam;
    int energyForStep;
    
    TeamEntity* units;
    TeamEntity* enemies;
    TeamEntity* aggressiveNPC;
    
    GameNeutralObjects* neutralObjs;
    
    
    Handler* firstHandler;
    Command* command;
    LogProxy* loggerP;
    GameVisualization* gameVisualization;
    
    
    cycleEnd gameCycle();
    
    void setMap();
    void setEnemies();
    void setBase();

    bool checkingVictory();
    void moveNPC();
    void spawnUForSurv();
    void spawnNPCForSurv();
    void updateLogs(setLog type = FORALL);
    void update(GameMap &map);
    
    //-----------------//
    class Memento{
        
    private:
        int* countTeam;
        int* energyForStep;
        GameMap* map;
        TeamEntity* units;
        TeamEntity* enemies;
        TeamEntity* aggressiveNPC;
        std::deque<TeamEntity*> teams;
        GameNeutralObjects* neutralObjs;
        
    public:
        Memento( GameMap* map, TeamEntity* units, TeamEntity* enemies,TeamEntity* aggressiveNPC,  GameNeutralObjects* neutralObjs, int* countTeam, int* energyForStep,  std::deque<TeamEntity*> teamss);
        friend std::ostream& operator <<(std::ostream& os, const GameMaster::Memento& meme);
        friend std::istream& operator >>(std::istream& os, const GameMaster::Memento& meme);
    };
    //-----------------//
    std::vector<GameMaster::Memento*> mem;

    Memento* makeMemento(){
        return new Memento(map, units, enemies,aggressiveNPC, neutralObjs, &countTeam, &energyForStep, teams);
    }
    
    

    
};



#endif /* GameMaster_h */


