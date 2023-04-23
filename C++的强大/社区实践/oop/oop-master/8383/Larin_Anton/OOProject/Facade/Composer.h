//
// Created by anton on 6/1/20.
//

#ifndef OOPROJECT_COMPOSER_H
#define OOPROJECT_COMPOSER_H

#include <memory>

#include "IFacade.h"
#include "../Command/Command/everything.h"

#include "../Command/Sender/ISender.h"



class Mediator;

class Actor;

class Composer: public IFacade {
public:

    //Composer(bool sync, const std::weak_ptr<Actor> &actor, const std::shared_ptr<ISender> &sender,const std::shared_ptr<Mediator> &mediator);

    Composer(bool sync, const std::weak_ptr<Actor> &actor, const std::shared_ptr<Mediator> &mediator);

    const std::pair<int, int> &getSelectionA() const override;

    const std::pair<int, int> &getSelectionB() const override;

    void setSelectionA(const std::pair<int, int> &selectionA) override;

    void setSelectionB(const std::pair<int, int> &selectionB) override;

    bool act() override;

    bool step() override;

    std::vector<std::vector<FlyCell>> getFW() override;

    bool summon(int x, int y, UnitClass unitClass) override;

    std::pair<int, std::pair<int, int>> getBaseStats(Devotion devotion) override;

    void exit() override;
    void restart() override;

    void setSync(bool sync);

    void setSender(const std::shared_ptr<ISender> &sender);

private:
    void send(std::unique_ptr<AbstractCommand> command);

private:


    bool sync;
    std::weak_ptr<Actor> actor;
    std::shared_ptr<ISender> sender;




private:
    std::shared_ptr<Mediator> mediator;
};


#endif //OOPROJECT_COMPOSER_H
