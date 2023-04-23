//
// Created by anton on 5/23/20.
//

#ifndef OOPROJECT_MEDIATOR_H
#define OOPROJECT_MEDIATOR_H

#include <memory>
#include <vector>

#include "Field.h"
#include "Factory/CommonFactory.h"

#include "FlyCell.h"

#include "Logger/AbstractLogger.h"


class Mediator {
private:
    std::shared_ptr<Field> field;
    std::shared_ptr<CommonFactory> factory;
    std::pair<int,int> selectionA;
    std::pair<int,int> selectionB;

    std::shared_ptr<AbstractLogger> logger;
public:
    void setLogger(const std::shared_ptr<AbstractLogger> &logger);

public:
    Mediator(const std::shared_ptr<Field> &field, const std::shared_ptr<CommonFactory> &factory);

    const std::pair<int, int> &getSelectionA() const;

    void setSelectionA(const std::pair<int, int> &selectionA);

    const std::pair<int, int> &getSelectionB() const;

    void setSelectionB(const std::pair<int, int> &selectionB);

public:
    int distance();
    std::pair<int,int> getDimensions();
    int getSteepnessAtB();

    std::pair<int,std::pair<int,int>>getBaseStats(Devotion devotion);
    bool createObject(int x, int y, Devotion devotion, CommonClass objectClass);

    bool step();
    bool act();

    void onBaseDestroyed(Devotion devotion);
    void onUnitsDestroyed(Devotion devotion);
    FlyCell getFlyCellAt(int x, int y);
    std::vector<std::vector<FlyCell>> getFW();



};


#endif //OOPROJECT_MEDIATOR_H

