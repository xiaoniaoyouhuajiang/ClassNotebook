//
// Created by anton on 3/4/20.
//

#ifndef PROJ_ENTITYBUSH_H
#define PROJ_ENTITYBUSH_H

#include "Entity.h"

class EntityBush:public Entity {
    wchar_t toChar() override;

    bool die(const GameObject &src, GameObject &dst) override;

public:
    EntityBush();

    GameObject &operator+=(const LandscapeProxy &b) override;

    GameObject &operator+=(const FieldCellProxy &b) override;

    GameObject &operator-=(const GameObject &b) override;

    bool isValidStep(int x, int y) override;

    bool step(int x, int y) override;

    UnitClass getUnitClass() const override;

};


#endif //PROJ_ENTITYBUSH_H
