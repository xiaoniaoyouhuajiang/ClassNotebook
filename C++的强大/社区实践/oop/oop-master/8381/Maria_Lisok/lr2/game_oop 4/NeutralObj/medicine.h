#ifndef MEDICINE_H
#define MEDICINE_H

#include "neutralObj.h"

class Medicine{
public:
    virtual ~Medicine()=default;
    virtual void use(Unit& unit)=0;
};
class Bandage : public Medicine{

public:
    void use(Unit &unit);
};

class  PowerPotion: public Medicine{

public:
    void use(Unit &unit);
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
};

#endif // MEDICINE_H
