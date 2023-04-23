#ifndef LAB2_CIVILIANSCREATOR_H
#define LAB2_CIVILIANSCREATOR_H

#include "creators/Creator.h"

class CiviliansCreator : public Creator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
