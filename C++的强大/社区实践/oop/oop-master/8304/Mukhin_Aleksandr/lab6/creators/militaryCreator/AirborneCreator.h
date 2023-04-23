#ifndef LAB2_AIRBORNECREATOR_H
#define LAB2_AIRBORNECREATOR_H


#include "MilitaryCreator.h"

class AirborneCreator : public MilitaryCreator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
