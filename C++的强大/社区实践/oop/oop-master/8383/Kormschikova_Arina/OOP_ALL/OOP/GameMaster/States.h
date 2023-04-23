
#ifndef States_h
#define States_h
class GameMaster;
class Rules;


class States{
protected:
    Rules* context;
public:
    States(Rules* rules):context(rules){};
    void setContext(Rules* context);
    virtual void actions() = 0;
    virtual ~States() {};
};


class GameCycleState: public States{
public:
    GameCycleState(Rules* rules):States(rules){};
    void actions() override;
};

class CheckingVictoryStates: public States{
public:
    CheckingVictoryStates(Rules* rules):States(rules){};
    void actions() override;
};


class CheckingVictoryForSurvStates: public States{
public:
    CheckingVictoryForSurvStates(Rules* rules):States(rules){};
    void actions() override;
};


class SwitchState: public States{
public:
    SwitchState(Rules* rules):States(rules){};
    void actions() override;
};

class BasePlacementState: public States{
public:
    BasePlacementState(Rules* rules):States(rules){};
    void actions() override;
};

class EndGameState: public States{
public:
    EndGameState(Rules* rules):States(rules){};
    void actions() override;
};

class NPCState:public States{
public:
    NPCState(Rules* rules):States(rules){};
    void actions() override;
};

class SpawnNPC:public States{
public:
    SpawnNPC(Rules* rules):States(rules){};
    void actions() override;
};
class SpawnUnitForSurv: public States{
public:
    SpawnUnitForSurv(Rules* rules):States(rules){};
    void actions() override;
};


#endif /* States_h */
