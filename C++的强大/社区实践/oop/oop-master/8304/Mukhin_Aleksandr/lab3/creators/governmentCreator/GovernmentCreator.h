#ifndef LAB2_GOVERNMENTCREATOR_H
#define LAB2_GOVERNMENTCREATOR_H


#include <creators/Creator.h>

class GovernmentCreator : public Creator {
public:
    std::shared_ptr<Unit> make_unit() const override;
};


#endif
