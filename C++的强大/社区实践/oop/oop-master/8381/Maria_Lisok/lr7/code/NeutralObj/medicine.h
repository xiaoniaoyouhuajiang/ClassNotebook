#ifndef MEDICINE_H
#define MEDICINE_H

#include "neutralObj.h"

class Medicine{
public:
    virtual ~Medicine()=default;
    virtual void use(Unit& unit)=0;
    virtual NeutralType type()=0;
};
class Bandage : public Medicine{

public:
    void use(Unit &unit);
    virtual NeutralType type();
};

class  PowerPotion: public Medicine{

public:
    void use(Unit &unit);
    virtual NeutralType type();
};


class GetMedicine : public NeutralObj
{
private:
    Medicine* medicine;
public:
    GetMedicine(Medicine*);
    void operator +=(Unit &unit);
    ~GetMedicine();
    string characteristic();
    string getType()const;
    NeutralType getTypeEnum();
};

#endif // MEDICINE_H
