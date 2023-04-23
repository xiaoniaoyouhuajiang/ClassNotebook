#ifndef ORK_H
#define ORK_H

#include "infantry.h"
class Ork : public Infantry{
public:
    Ork();
    string getName();
    Unit* copyItem();
    UnitsType getTypeEnum() const;
};

#endif // ORK_H
