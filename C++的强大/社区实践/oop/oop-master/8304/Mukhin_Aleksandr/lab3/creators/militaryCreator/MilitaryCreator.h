#ifndef LAB2_MILITARYCREATOR_H
#define LAB2_MILITARYCREATOR_H

#include "creators/Creator.h"

class MilitaryCreator : public Creator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
