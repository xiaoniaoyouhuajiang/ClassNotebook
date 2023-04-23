#ifndef LAB1_ARCHERSSENIORCREATOR_H
#define LAB1_ARCHERSSENIORCREATOR_H
#include "ArchersCreator.h"

class ArchersSeniorCreator : public ArchersCreator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
