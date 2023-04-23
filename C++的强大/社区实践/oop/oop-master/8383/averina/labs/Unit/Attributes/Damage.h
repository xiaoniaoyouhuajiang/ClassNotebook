#ifndef OOP_DAMAGE_H
#define OOP_DAMAGE_H



class Damage
{
public:
    void set(int damage, int range, int cost);
    int getDamage();
    int getRange();
    int getCost();

private:
    int damage_;        //   наносивый урон
    int damageRange_;  //  радиус атаки
    int damageCost_;  //  стоимость атаки
};


#endif //OOP_DAMAGE_H
