#ifndef LAB1_INFANTRYCREATOR_H
#define LAB1_INFANTRYCREATOR_H
#include "Unit.h"
#include "Infantry.h"

class InfantryCreator : public Creator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};
#endif
