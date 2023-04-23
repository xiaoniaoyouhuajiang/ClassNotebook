#ifndef LAB1_ARCHERSJUNIORCREATOR_H
#define LAB1_ARCHERSJUNIORCREATOR_H

#include "ArchersCreator.h"

class ArchersJuniorCreator : public ArchersCreator{
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
