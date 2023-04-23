#ifndef LAB1_INFANTRYSENIORCREATOR_H
#define LAB1_INFANTRYSENIORCREATOR_H
#include "InfantryCreator.h"

class InfantrySeniorCreator : public InfantryCreator{
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
