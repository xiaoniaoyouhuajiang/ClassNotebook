#ifndef heavyarmorfactory_hpp
#define heavyarmorfactory_hpp

#include "armorfactory.hpp"

#include <stdio.h>

class HeavyArmorFactory : public ArmorFactory
{
public:

    virtual std::shared_ptr<Armor> createArmor() const override;
};

#endif /* heavyarmorfactory_hpp */
