#pragma once

#include "Field/Field.h"

class Game;
class Landscape;
class IUnit;
class Base;


class GameMediator
{
    friend class Game;

public:
    bool unitMove(IUnit* unit, Point point);
    bool unitNeutralInterraction(IUnit* unit);
    bool unitUnificationAccess(IUnit* active, IUnit* passive);
    bool baseProductionAccess(Base* base);

    bool checkNeighborPoint(Point one, Point supposeNeighbor);
    uint16_t distance(Point one, Point two);

    ILandscape* getLandscape(Point point);

private:
    GameMediator(Game* game);

private:
    Game* game;
};
