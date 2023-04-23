//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_FACADERECIEVER_H
#define OOPROJECT_FACADERECIEVER_H

#include <memory>


#include "IFacade.h"
#include "State.h"
#include "../Mediator.h"

#include "../Command/Sender/ISender.h"
class FacadeReciever:public IFacade,public std::enable_shared_from_this<FacadeReciever> {
public:
    FacadeReciever(const std::shared_ptr<Mediator> &mediator);

    void init(bool firstA, std::shared_ptr<Actor> actorA, std::shared_ptr<Actor> actorB);

    const std::pair<int, int> &getSelectionA() const override;

    const std::pair<int, int> &getSelectionB() const override;

    void setSelectionA(const std::pair<int, int> &selectionA) override;

    void setSelectionB(const std::pair<int, int> &selectionB) override;

    bool act() override;

    bool step() override;

    std::vector<std::vector<FlyCell>> getFW() override;

    bool summon(int x, int y, UnitClass unitClass) override;

    void next();

    //void loop();

    void exit()override ;
    void restart()override;
    void turn();

    std::weak_ptr<Actor> whosTurn();
    Devotion turnDevotion();


private:
    bool exitFlag;
public:
    bool isExitFlag() const;

private:
    bool restartFlag;
public:
    bool isRestartFlag() const;

    std::pair<int, std::pair<int, int>> getBaseStats(Devotion devotion) override;


private:
    //std::shared_ptr<ISender> sender;
    std::shared_ptr<Mediator> mediator;
    std::shared_ptr<State> activeState;
    std::shared_ptr<IFacade> stateA;
    std::shared_ptr<IFacade> stateB;



};


#endif //OOPROJECT_FACADERECIEVER_H
