#pragma once

#include "Trivia/Point.h"

class Object;
class ILandscape;
class IUnit;
class Base;
class NeutralContext;


class Cell
{
public:
    Cell();
    Cell(Point point, ILandscape* landscape);
    Cell(Cell&& oldCell); // перемещение
    ~Cell();

    Cell& operator=(Cell&& oldCell);

    Point getPoint();
    uint16_t getX();
    uint16_t getY();

    ILandscape* getLandscape();

    bool setUnit(IUnit* unit);
    IUnit* getUnit();
    void removeUnit();

    bool setBase(Base* base);
    Base* getBase();
    void removeBase();

    bool setContext(NeutralContext* context);
    NeutralContext* getContext();

    bool isUnitFree();
    bool isBuildingFree();
    uint16_t getBuildingGroupType();

private:
    Point point;
    ILandscape* landscape;
    IUnit* unit;
    union {
        void* building;
        Base* base;
        NeutralContext* context;
    };
    uint16_t buildingType; // 0 - base, 1 - context
};

