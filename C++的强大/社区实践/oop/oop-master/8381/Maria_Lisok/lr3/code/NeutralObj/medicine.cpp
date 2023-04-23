#include "medicine.h"

GetMedicine::GetMedicine(Medicine * med) : medicine(med)
{

}
string GetMedicine::getType()const{
    return "neutral";
}

NeutralType GetMedicine::getTypeEnum()
{
    return medicine->type();
}
void GetMedicine::operator +=(Unit &unit)
{
    medicine->use(unit);
}

GetMedicine::~GetMedicine()
{
    delete medicine;
}


string GetMedicine::characteristic()
{
    return "GetMedicine";
}

void Bandage::use(Unit &unit)
{
    unit.getAttributes()->setHealth(unit.getAttributes()->getHealth()+20);
}

NeutralType Bandage::type()
{
    return BANDAGE;
}

void PowerPotion::use(Unit &unit)
{
    unit.getAttributes()->setHealth(unit.getAttributes()->getHealth()+40);
}

NeutralType PowerPotion::type()
{
    return POWERPOTION;
}

