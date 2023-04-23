
#ifndef OOP_MANA_H
#define OOP_MANA_H

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
    int get();
    void actRecovered(int recover);  // восстановление маны
    void actReduced(int decrease);  //  уменьшение маны
private:
    int mana_;
    int maxMana_;
};




#endif //OOP_MANA_H
