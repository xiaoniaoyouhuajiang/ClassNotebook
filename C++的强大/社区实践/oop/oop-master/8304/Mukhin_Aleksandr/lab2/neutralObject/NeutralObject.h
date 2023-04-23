#ifndef LAB2_NEUTRALOBJECT_H
#define LAB2_NEUTRALOBJECT_H


#include <HealthPoints.h>
#include <Attack.h>
#include "AbstractNeutralObject.h"

class NeutralObject : public AbstractNeutralObject {
public:
    NeutralObject(int def, int att, int intell) : defense(def), attack(att), intelligence(intell) {}
    HealthPoints defense;
    Attack attack;
    int intelligence{};

    int get_health() const override;
    int get_attack() const override;
    int get_intelligence() const override;
};


#endif
