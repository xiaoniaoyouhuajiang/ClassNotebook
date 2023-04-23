

#ifndef GameBlock_h
#define GameBlock_h

#include <stdio.h>
#include "Interfaces.h"

class Unit;
class NeutralObject;
class Base;

class Landscape;


class GameBlock: public IGameBlock{
    
public:
    Unit* unitOnBlock;
    NeutralObject* objectOnBlock;
    Base* baseOnBlock;
    Landscape* landscape;
    
    GameBlock();
    bool setUnit(Unit* unit) override;
    bool setBase(Base* base) override;
    bool setObject(NeutralObject* obj) override;
    bool deleteUnit() override;
    bool isEmpty() override;
};

class Landscape: public ILandscape{
public:
    bool availability;
    char type;
};

class Grass: public Landscape{
public:
    Grass();
};

class Water: public Landscape{
public:
    Water();
};

class Forest: public Landscape{
public:
    Forest();
};

#endif /* GameBlock_h*/
