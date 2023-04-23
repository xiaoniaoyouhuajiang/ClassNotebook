
#ifndef noarmor_hpp
#define noarmor_hpp

#include "armor.hpp"

#include <stdio.h>

 class NoArmor : public Armor
 {
 public:
     explicit NoArmor();

     NoArmor(const NoArmor& armor);
     NoArmor& operator=(const NoArmor& armor);

     virtual double getResistance() const override;
     virtual std::string getAmorType() const override;
     
     virtual std::shared_ptr<Armor> clone() const override;

 };

#endif /* noarmor_hpp */
