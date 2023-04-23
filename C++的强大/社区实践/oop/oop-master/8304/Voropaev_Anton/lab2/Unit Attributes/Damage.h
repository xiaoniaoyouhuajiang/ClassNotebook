#ifndef OOP_DAMAGE_H
#define OOP_DAMAGE_H


class Damage {
public:
    Damage();
    ~Damage() = default;
    Damage(int d, int r);
    int getDamage() const;
    void setDamage(int d);
    int getRange() const;
    void setRange(int r);
    void DecreaseDmg(int debuff);
    void IncreaseDmg(int buff);
    void IncreaseRange(int buff);
private:
    int damage;
    int range;
};

#endif //OOP_DAMAGE_H
