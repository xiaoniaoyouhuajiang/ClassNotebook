#ifndef LAB1_CAVALRYCREATOR_H
#define LAB1_CAVALRYCREATOR_H
#include "Creator.h"

class CavalryCreator : public Creator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
