#ifndef LAB2_LANDSCAPE_H
#define LAB2_LANDSCAPE_H

#include "HealthPoints.h"
#include "Attack.h"
#include "AbstractLandscape.h"

class Landscape : public AbstractLandscape {
public:
    Landscape() = default;
    Landscape(int def, int att, int intell, bool stand) : defense(def), attack(att), intelligence(intell), can_stand(stand) {}
    HealthPoints defense;
    Attack attack;
    int intelligence{};
    int get_health() const override;
    int get_attack() const override;
    int get_intelligence() const override;
    bool can_stand{};
};


#endif
