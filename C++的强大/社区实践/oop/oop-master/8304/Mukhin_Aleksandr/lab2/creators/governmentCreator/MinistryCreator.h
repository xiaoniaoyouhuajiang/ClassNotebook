#ifndef LAB2_MINISTRYCREATOR_H
#define LAB2_MINISTRYCREATOR_H


#include "GovernmentCreator.h"

class MinistryCreator : public GovernmentCreator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
