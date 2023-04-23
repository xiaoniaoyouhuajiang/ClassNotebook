#ifndef SWARDMAN_H
#define SWARDMAN_H

#include "infantry.h"

class Swardman : public Infantry{
public:
    Swardman();
    string getName();
    Unit* copyItem();
    UnitsType getTypeEnum() const;

};

#endif // SWARDMAN_H
