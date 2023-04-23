#ifndef UNIT_H
#define UNIT_H

#include "attributes.h"
#include <iostream>
#include "moveMediator.h"
#include "subject.h"
using namespace std;
class Unit : public Subject{
public:
    Unit()=default;
    Unit(Unit&);
    virtual ~Unit();

    virtual bool isMovable();

    virtual void setMoveMediator(MoveMediator *value);

    virtual Attributes* getAttributes() const;
    void setAttributesHealth(int);
    void setAttributesArmor(int);
    void setAttributesAttack(int);

    virtual void move(int x, int y);

    virtual std::string getName()=0;

    virtual Unit* copyItem() = 0;

    virtual string characteristic();

    string getType() const;

protected:
    std::string name;
    bool movable=true;
    Attributes* attributes;
    MoveMediator* moveMediator;

};


#endif // UNIT_H
