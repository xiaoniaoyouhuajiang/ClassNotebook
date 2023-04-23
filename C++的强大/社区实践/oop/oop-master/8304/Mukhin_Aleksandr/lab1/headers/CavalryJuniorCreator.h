#ifndef LAB1_CAVALRYJUNIORCREATOR_H
#define LAB1_CAVALRYJUNIORCREATOR_H
#include "CavalryCreator.h"

class CavalryJuniorCreator : public CavalryCreator{
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
