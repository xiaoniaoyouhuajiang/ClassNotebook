//
// Created by Artem Butko on 08/05/2020.
//

#ifndef OOP_NEW_DAMAGE_H
#define OOP_NEW_DAMAGE_H

/*
 * Damage -- класс очков урона, который может
 * нанести объект.
 * -----------------------------------------
 * damage_ -- урон, который наносит объект.
 * damageRange_ -- радиус, в котором объект
 * может атаковать.
 * damageCost_ -- стоимость атаки (очков вы-
 * носливости.
 */

class Damage
{
public:
    void set(int damage, int range, int cost);
    int getDamage();
    int getRange();
    int getCost();

private:
    int damage_;
    int damageRange_;
    int damageCost_;
};


#endif //OOP_NEW_DAMAGE_H
