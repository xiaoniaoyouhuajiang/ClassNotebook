
#ifndef NeutralObject_h
#define NeutralObject_h
#include "Interfaces.h"
#include <sstream>

class Unit;
class LogProxy;

class NeutralObject: public INeutralObject{
public:
    int x, y;
    int hitPoint;
    char type;
    LogProxy* loggerP;

    NeutralObject();
    void setXY(int x, int y) override;
    void getDamage(int damage) override;
    NeutralObject& operator += (Unit& unit);
    virtual void setLog(LogProxy* logger) override;
    
    friend std::ostream& operator <<(std::ostream& os, const NeutralObject& nObj);
    
};

class MrWitcher: public NeutralObject{
public:
    int nerves;
    MrWitcher();
    void action(Unit& unit) override;
    //random phrases
};

class Bonfire: public NeutralObject{
public:
    int healing;
    Bonfire();
    void action(Unit& unit) override;
};

class Grave: public NeutralObject{
public:
    Grave();
    void action(Unit& unit) override;
    //it will be mine
};

class Bird: public NeutralObject{
public:
    int damage;
    Bird();
    Bird(int damage);
    void action(Unit& unit) override;
    //random tweet and damage!11
};


#endif /* NeutralObject_h */


