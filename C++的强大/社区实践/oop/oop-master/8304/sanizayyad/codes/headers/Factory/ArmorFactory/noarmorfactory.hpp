#ifndef noarmorfactory_hpp
#define noarmorfactory_hpp

#include "armorfactory.hpp"

#include <stdio.h>

class NoArmorFactory : public ArmorFactory
{
public:

    virtual std::shared_ptr<Armor> createArmor() const override;
};

#endif /* noarmorfactory_hpp */
