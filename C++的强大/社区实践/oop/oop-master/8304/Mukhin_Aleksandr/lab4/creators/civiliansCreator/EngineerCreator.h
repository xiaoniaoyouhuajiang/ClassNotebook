#ifndef LAB2_ENGINEERCREATOR_H
#define LAB2_ENGINEERCREATOR_H


#include "CiviliansCreator.h"

class EngineerCreator : public CiviliansCreator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
