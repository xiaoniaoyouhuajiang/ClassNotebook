#ifndef OOP_OBJECT_H
#define OOP_OBJECT_H

#include "Unit Attributes/Health.h"
#include "Unit Attributes/Damage.h"
#include "Unit Attributes/Armor.h"
#include "Unit Attributes/Location.h"

class Object: public Health, public Armor, public Location, public Damage {
public:

    Object() = default;
    virtual ~Object() = 0;
    virtual Object* clone() = 0;


};


#endif //OOP_OBJECT_H
