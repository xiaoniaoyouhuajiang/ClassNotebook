#ifndef lightarmor_hpp
#define lightarmor_hpp

#include "armor.hpp"

#include <stdio.h>


class LightArmor : public Armor
{
public:
    explicit LightArmor();

    LightArmor(const LightArmor& armor);
    LightArmor& operator=(const LightArmor& armor);

    virtual std::shared_ptr<Armor> clone() const override;

    virtual double getResistance() const override;
    virtual std::string getAmorType() const override;
    

};

#endif /* lightarmor_hpp */
