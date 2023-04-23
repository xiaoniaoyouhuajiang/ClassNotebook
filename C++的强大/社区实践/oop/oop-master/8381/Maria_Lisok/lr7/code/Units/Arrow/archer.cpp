#include "archer.h"

Archer::Archer(){
    name = "Archer";
    attributes = new Attributes();
    attributes->setAllAttributes(20, 10, 5);
}


string Archer::getName()
{
    return "archer";
}

Unit *Archer::copyItem()
{

    return new Archer(*this);

}

UnitsType Archer::getTypeEnum() const
{
    return  ARCHER;
}
