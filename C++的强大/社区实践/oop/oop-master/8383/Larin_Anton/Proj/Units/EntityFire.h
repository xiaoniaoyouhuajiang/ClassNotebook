//
// Created by anton on 3/4/20.
//

#ifndef PROJ_ENTITYFIRE_H
#define PROJ_ENTITYFIRE_H

#include "Entity.h"

class EntityFire : public Entity {
public:
    EntityFire();

    wchar_t toChar() override;

    bool die(const GameObject &src, GameObject &dst) override;

    GameObject &operator+=(const LandscapeProxy &b) override;

    GameObject &operator+=(const FieldCellProxy &b) override;

    GameObject &operator-=(const GameObject &b) override;

    bool isValidStep(int x, int y) override;

    bool step(int x, int y) override;

    UnitClass getUnitClass() const override;

};


#endif //PROJ_ENTITYFIRE_H
