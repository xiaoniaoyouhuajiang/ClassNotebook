#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H


class Attribute
{
private:
    int value;
    int bonus;
public:
    Attribute() { }
    Attribute(int value, int bonus = 0) : value(value), bonus(bonus) { }
    Attribute(const Attribute& attribute)
    {
        this->value = attribute.value;
        this->bonus = attribute.bonus;
    }
    void setValue(int newValue) { this->value = newValue; }
    int getValue() const { return value; }

    void setBonus(int newBonus) { this->bonus = newBonus; }
    int getBonus() const { return bonus; }
};

#endif // ATTRIBUTE_H
