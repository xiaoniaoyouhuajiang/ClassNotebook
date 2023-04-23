
#ifndef mediumarmor_hpp
#define mediumarmor_hpp

#include "armor.hpp"

#include <stdio.h>


class MediumArmor : public Armor
{
public:
    explicit MediumArmor();

    MediumArmor(const MediumArmor& armor);
    MediumArmor& operator=(const MediumArmor& armor);

    virtual std::shared_ptr<Armor> clone() const override;

    virtual double getResistance() const override;
    virtual std::string getAmorType() const override;
    

};

#endif /* mediumarmor_hpp */
