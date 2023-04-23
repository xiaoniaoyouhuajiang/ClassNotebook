//
// Created by Artem Butko on 08/05/2020.
//

#ifndef OOP_NEW_MANA_H
#define OOP_NEW_MANA_H

/*
 * Mana -- класс очков маны объекта.
 * -----------------------------------------
 * mana_ -- текущие очки маны.
 * maxMana_ -- максимальные очки маны.
 */

class Mana
{
public:
    void set(int mana);
    void actRecovered(int recover);
    void actReduced(int decrease);
private:
    int mana_;
    int maxMana_;
};


#endif //OOP_NEW_MANA_H
