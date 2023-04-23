#ifndef STATE_H
#define STATE_H


#include "gameinterface.h"
#include "Kind.h"
#include <memory>
#include "Field.h"
#include "Facade.h"
#include "statetype.h"


class State : public GameInterface
{
protected:
    StateType type;
    Kind kind;
    int playerNum;
    std::shared_ptr<Field> field;
    std::shared_ptr<Facade> facade;
    int yT;
    int yU;
    std::shared_ptr<State> nextState;
    int resources;

public:
    State(Kind kind, int num, std::shared_ptr<Field> field, std::shared_ptr<Facade> facade);
    Kind getKind();
    int getPlayerNum();
    virtual void create(int xT, int xU, UnitType type);
    virtual void endStep();
    void setNextState(std::shared_ptr<State> state);
    std::shared_ptr<State> getNextState();
    void renewResources();
    int getResources();
    StateType getType();
    void setResources(int resources);
};

#endif // STATE_H
