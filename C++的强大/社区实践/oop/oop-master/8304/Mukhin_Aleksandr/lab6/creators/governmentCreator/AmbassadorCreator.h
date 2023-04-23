#ifndef LAB2_AMBASSADORCREATOR_H
#define LAB2_AMBASSADORCREATOR_H


#include "GovernmentCreator.h"

class AmbassadorCreator : public GovernmentCreator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
