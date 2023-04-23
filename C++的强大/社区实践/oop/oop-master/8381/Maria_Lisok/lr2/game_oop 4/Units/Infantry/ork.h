#ifndef ORK_H
#define ORK_H

#include "infantry.h"
class Ork : public Infantry{
public:
    Ork();
    string getName();
    Unit* copyItem();
};

#endif // ORK_H
