#ifndef OOP_ARMOR_H
#define OOP_ARMOR_H


class Armor {
public:

    Armor();
    ~Armor() = default;
    explicit Armor(int a);
    int getArmor() const;
    void setArmor(int a);
    void DecreaseArmor(int debuff);
    void IncreaseArmor(int buff);

private:
    int armor;
};


#endif //OOP_ARMOR_H
