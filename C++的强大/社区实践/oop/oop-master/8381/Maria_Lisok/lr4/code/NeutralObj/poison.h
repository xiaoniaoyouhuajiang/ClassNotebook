#ifndef POISON_H
#define POISON_H

#include "neutralObj.h"


class Poison{

public:
    virtual ~Poison()=default;
    virtual void use(Unit& unit)=0;
    virtual NeutralType type()=0;
};

class Covid19: public Poison{

public:
    void use(Unit &unit);
    virtual NeutralType type();
};

class Covid37: public Poison{

public:
    void use(Unit &unit);
    virtual NeutralType type();
};

class DrinkPoison : public NeutralObj
{
private:
    Poison* poison;
public:
    DrinkPoison(Poison*);

    void operator +=(Unit &unit);
    ~DrinkPoison();
    string characteristic();
    string getType()const;
    NeutralType getTypeEnum();
};

#endif // POISON_H
