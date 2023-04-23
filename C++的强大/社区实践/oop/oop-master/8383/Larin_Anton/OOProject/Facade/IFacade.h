//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_IFACADE_H
#define OOPROJECT_IFACADE_H

#include <utility>
#include <vector>

#include "../FlyCell.h"
#include "../Stats.h"

//class FlyCell;

class IFacade {
public:
    virtual const std::pair<int, int> &getSelectionA() const=0;
    virtual const std::pair<int, int> &getSelectionB() const=0;
    virtual void setSelectionA(const std::pair<int, int> &selectionA)=0;
    virtual void setSelectionB(const std::pair<int, int> &selectionB)=0;
    virtual bool act()=0;
    virtual bool step()=0;
    virtual std::vector<std::vector<FlyCell>> getFW() = 0;
    virtual bool summon(int x ,int y, UnitClass unitClass)=0;
    virtual void exit()=0;
    virtual void restart()=0;
    virtual std::pair<int, std::pair<int, int>> getBaseStats(Devotion devotion) =0;
};


#endif //OOPROJECT_IFACADE_H
