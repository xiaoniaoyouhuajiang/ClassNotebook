//
// Created by mensch on 4/4/20.
//

#ifndef OOP_LABS_ARMOR_H
#define OOP_LABS_ARMOR_H


class Armor {

protected:
    int physicDamageReduction;
    int magicDamageReduction;
    double weight;
public:
    Armor() = default;
    virtual ~Armor() = default;
};


#endif //OOP_LABS_ARMOR_H
