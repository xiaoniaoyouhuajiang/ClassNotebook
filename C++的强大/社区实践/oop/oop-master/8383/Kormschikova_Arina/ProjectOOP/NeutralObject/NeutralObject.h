
#ifndef NeutralObject_h
#define NeutralObject_h
#include "Interfaces.h"
class Unit;

class NeutralObject: public INeutralObject{
public:
    int hitPoint;
    char type;
    NeutralObject();
    void getDamage(int damage) override;
    NeutralObject& operator += (Unit& unit);
   
    
    
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


