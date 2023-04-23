//
// Created by Artem Butko on 08/05/2020.
//

#ifndef OOP_NEW_HEALTH_H
#define OOP_NEW_HEALTH_H

/*
 * Health -- класс очков здоровья объекта.
 * -----------------------------------------
 * health_ -- текущие очки здоровья.
 * maxHealth -- максимальные очки здоровья.
 * isDead -- статус объекта (жив/мертв).
 */

class Health
{
public:
    void set(int health);
    int get();
    void actDamaged(int damage);
    void actHealed(int heal);

private:
    int health_;
    int maxHealth_;
    bool isDead;
};


#endif //OOP_NEW_HEALTH_H
