#ifndef heavyarmor_hpp
#define heavyarmor_hpp

#include "armor.hpp"

#include <stdio.h>


class HeavyArmor : public Armor
{
public:
    explicit HeavyArmor();

    HeavyArmor(const HeavyArmor& armor);
    HeavyArmor& operator=(const HeavyArmor& armor);

    virtual std::shared_ptr<Armor> clone() const override;

    virtual double getResistance() const override;
    virtual std::string getAmorType() const override;
    

};

#endif /* heavyarmor_hpp */
