
#ifndef Rules_h
#define Rules_h

#include <stdio.h>

enum mode{ONEPLAYER = 1, TWOPLAYERS = 2, SECONDRULE = 3};

class States;
class GameMaster;


class Rules{
private:
    States* currentState;

public:
    mode modeR;
    GameMaster* gameMaster;
    int countCycle;
    int maxCycle;
    Rules(GameMaster* gameMaster, mode modeR):gameMaster(gameMaster),currentState(nullptr), modeR(modeR), countCycle(0), maxCycle(10){};
    void transitionTo(States* newState);
    bool request();
    virtual void gameProcess() =0;

};

class RuleBattleBetweenTeams: public Rules{
public:
    RuleBattleBetweenTeams(GameMaster* gameMaster, mode modeR):Rules(gameMaster, modeR){};
    void gameProcess() override;
};


class RuleSurvival: public Rules{

public:
    RuleSurvival(GameMaster* gameMaster, mode modeR):Rules(gameMaster, modeR){};
    void gameProcess() override;
};




#endif /* Rules_h */
