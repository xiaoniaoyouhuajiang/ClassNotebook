#ifndef LAB1_CAVALRYSENIORCREATOR_H
#define LAB1_CAVALRYSENIORCREATOR_H
#include "CavalryCreator.h"

class CavalrySeniorCreator : public CavalryCreator{
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
