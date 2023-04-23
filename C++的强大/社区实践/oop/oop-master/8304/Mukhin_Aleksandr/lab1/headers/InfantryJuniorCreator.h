#ifndef LAB1_INFANTRYJUNIORCREATOR_H
#define LAB1_INFANTRYJUNIORCREATOR_H

#include "InfantryCreator.h"

class InfantryJuniorCreator : public InfantryCreator{
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
