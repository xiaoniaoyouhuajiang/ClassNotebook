#ifndef lightarmorfactory_hpp
#define lightarmorfactory_hpp

#include "armorfactory.hpp"

#include <stdio.h>

class LightArmorFactory : public ArmorFactory
{
public:

    virtual std::shared_ptr<Armor> createArmor() const override;
};


#endif /* lightarmorfactory_hpp */
