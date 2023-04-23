#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H


class Attributes
{
private:
    int health;
    int armor;
    int attack;
public:
    Attributes();

    int getHealth() const;
    void setHealth(int value);

    int getArmor() const;
    void setArmor(int value);

    int getAttack() const;
    void setAttack(int value);

    void setAllAttributes(int, int, int);

};

#endif // ATTRIBUTES_H
