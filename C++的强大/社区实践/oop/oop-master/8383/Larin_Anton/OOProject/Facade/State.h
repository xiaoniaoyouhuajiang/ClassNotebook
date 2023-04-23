//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_STATE_H
#define OOPROJECT_STATE_H

#include <memory>

#include "../Actor/Actor.h"

#include "IFacade.h"

class Mediator;
class FacadeReciever;

class State:public IFacade {
    friend class FacadeReciever;
private:
    std::weak_ptr<State> nextState;
public:
    const std::weak_ptr<State> &getNextState() const;

    void setNextState(const std::weak_ptr<State> &nextState);

private:
    std::shared_ptr<Mediator> mediator;
    std::weak_ptr<FacadeReciever> facadeReciever;
    std::shared_ptr<Actor> actor;
    Devotion devotion;
public:
    Devotion getDevotion() const;


public:
    State(const std::shared_ptr<Mediator> &mediator, const std::weak_ptr<FacadeReciever> &facadeReciever,
          const std::shared_ptr<Actor> &actor, Devotion devotion);

    void onEnter();

    const std::pair<int, int> &getSelectionA() const override;

    const std::pair<int, int> &getSelectionB() const override;

    void setSelectionA(const std::pair<int, int> &selectionA) override;

    void setSelectionB(const std::pair<int, int> &selectionB) override;

    bool act() override;

    bool step() override;

    std::vector<std::vector<FlyCell>> getFW() override;

    void next();

    bool summon(int x, int y, UnitClass unitClass) override;

    void exit() override;

    void restart() override;

    std::pair<int, std::pair<int, int>> getBaseStats(Devotion devotion) override;

};


#endif //OOPROJECT_STATE_H
