#ifndef ARMOR_H
#define ARMOR_H

#include <memory>


constexpr double NO_ARMOR = 1;
constexpr double LIGHT_ARMOR = 0.8;
constexpr double MEDIUM_ARMOR = 0.6;
constexpr double HEAVY_ARMOR = 0.5;


class Armor
{
public:
    virtual ~Armor() = default;

    virtual double getResistance() const = 0;

    virtual std::shared_ptr<Armor> clone() const = 0;

protected:
    void doCopy(const Armor& armor);

protected:
    double resistance;
};

#endif // ARMOR_H
