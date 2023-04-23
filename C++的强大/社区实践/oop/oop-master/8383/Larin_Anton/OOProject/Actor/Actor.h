//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_ACTOR_H
#define OOPROJECT_ACTOR_H

#include <memory>
#include <string>
#include <fstream>
#include "../Facade/IFacade.h"


class Actor: protected IFacade {
protected:
    std::shared_ptr<IFacade> composer;
public:
//  Actor(const std::shared_ptr<IFacade> &composerA);

    //Actor();

    Actor(const std::string &name);

    void setComposer(const std::shared_ptr<IFacade> &composer);

    std::string name;

public:
    virtual void notify(std::string)=0;
    virtual void turn()=0 ;

    bool save(std::string fileName);
protected:
    const std::pair<int, int> &getSelectionA() const override;

    const std::pair<int, int> &getSelectionB() const override;

    void setSelectionA(const std::pair<int, int> &selectionA) override;

    void setSelectionB(const std::pair<int, int> &selectionB) override;

    bool act() override;

    bool step() override;

    bool summon(int x, int y, UnitClass unitClass) override;

    void exit() override;
    void restart() override;

protected:
    std::vector<std::vector<FlyCell>> getFW() override;

    std::pair<int, std::pair<int, int>> getBaseStats(Devotion devotion) override;
};


#endif //OOPROJECT_ACTOR_H
