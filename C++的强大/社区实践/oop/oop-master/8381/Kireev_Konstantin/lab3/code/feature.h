#ifndef FEATURE_H
#define FEATURE_H


class Feature
{
private:
    int value;
    int bonus;

public:
    Feature()
    {
    }

    Feature(int value, int bonus = 0)
        : value(value)
        , bonus(bonus)
    {
    }

    Feature(const Feature& attribute)
    {
        this->value = attribute.value;
        this->bonus = attribute.bonus;
    }

    void setValue(int newValue)
    {
        this->value = newValue;
    }
    int getValue() const
    {
        return value;
    }

    void setBonus(int newBonus)
    {
        this->bonus = newBonus;
    }
    int getBonus() const
    {
        return bonus;
    }
};

#endif // FEATURE_H
