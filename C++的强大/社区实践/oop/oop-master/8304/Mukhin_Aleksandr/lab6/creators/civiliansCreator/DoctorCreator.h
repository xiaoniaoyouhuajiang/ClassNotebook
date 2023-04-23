#ifndef LAB2_DOCTORCREATOR_H
#define LAB2_DOCTORCREATOR_H


#include "CiviliansCreator.h"

class DoctorCreator : public CiviliansCreator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
