#ifndef LAB2_SPECIALFORCESCREATOR_H
#define LAB2_SPECIALFORCESCREATOR_H


#include "MilitaryCreator.h"

class SpecialForcesCreator : public MilitaryCreator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
