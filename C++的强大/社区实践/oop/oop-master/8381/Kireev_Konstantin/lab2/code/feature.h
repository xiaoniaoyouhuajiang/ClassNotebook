#ifndef FEATURE_H
#define FEATURE_H

class Feature
{
private:
    int value;
    int extra;

public:
    Feature()
    {
    }

    Feature(int value, int extra = 0)
        : value(value)
        , extra(extra)
    {
    }

    Feature(const Feature& attribute)
    {
        this->value = attribute.value;
        this->extra = attribute.extra;
    }

    void setValue(int newValue)
    {
        this->value = newValue;
    }
    int getValue() const
    {
        return value;
    }

    void setExtra(int newBonus)
    {
        this->extra = newBonus;
    }
    int getExtra() const
    {
        return extra;
    }
};

#endif // FEATURE_H
