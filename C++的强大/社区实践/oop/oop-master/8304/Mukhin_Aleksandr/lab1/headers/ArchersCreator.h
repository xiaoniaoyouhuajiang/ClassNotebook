#ifndef LAB1_ARCHERSCREATOR_H
#define LAB1_ARCHERSCREATOR_H
#include "Unit.h"

class ArchersCreator : public Creator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
