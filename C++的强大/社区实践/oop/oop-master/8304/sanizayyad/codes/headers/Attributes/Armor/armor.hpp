
#ifndef armor_hpp
#define armor_hpp

#include <stdio.h>
#include <iostream>

constexpr double NO_ARMOR = 0.0;
constexpr double LIGHT_ARMOR = 0.25;
constexpr double MEDIUM_ARMOR = 0.5;
constexpr double HEAVY_ARMOR = 0.75;

class Armor
{
public:
    virtual ~Armor() = default;

    virtual double getResistance() const = 0;
    virtual std::string getAmorType() const = 0;
    virtual void getArmorInfo();

    virtual std::shared_ptr<Armor> clone() const = 0;

protected:
    void doCopy(const Armor& armor);
protected:
    std::string armorType;
    double resistance;
};

#endif /* armor_hpp */
