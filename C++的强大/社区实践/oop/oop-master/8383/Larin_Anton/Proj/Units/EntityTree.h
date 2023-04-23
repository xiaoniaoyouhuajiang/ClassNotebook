//
// Created by anton on 3/4/20.
//

#ifndef PROJ_ENTITYTREE_H
#define PROJ_ENTITYTREE_H

#include "Entity.h"

class EntityTree : public Entity {
public:
    EntityTree();

    wchar_t toChar() override;

    bool die(const GameObject &src, GameObject &dst) override;

    GameObject &operator+=(const LandscapeProxy &b) override;

    GameObject &operator+=(const FieldCellProxy &b) override;

    GameObject &operator-=(const GameObject &b) override;

    bool isValidStep(int x, int y) override;

    bool step(int x, int y) override;

    UnitClass getUnitClass() const override;

};


#endif //PROJ_ENTITYTREE_H
