#ifndef UNIT_H
#define UNIT_H


class Unit{
protected:
public:
    Unit();
    int attackRange;
    int cost;
    int hp;
    int force;
    char sym;
    struct id{                  //будет двузначным числом, указывающим положение юнита в массиве,
        int code;               //чтобы метод move мог легко достать из массива нужного юнита
        int index;              // и поменять ему координаты
    }id;
    int x, y;
    bool compFlag = 1;

};

class Warrior: public Unit
{
private:

public:

};

class Mage: public Unit
{
public:

};

class Saboteur: public Unit
{
public:
};

class Gladiator: public Warrior{
public:
};

class Gunslinger: public Warrior{
public:
};

class Healer:public Mage{
public:
};

class Wizard:public Mage{
public:
};

class Jew:public Saboteur{
public:
};

class Kamikadze:public Saboteur{
public:
};


// юниты игрока 1

class Player1Gladiator: public Gladiator{
public:
    Player1Gladiator(int x, int y);
};

class Player1Gunslinger: public Gunslinger {
public:
    Player1Gunslinger(int x, int y);
};

class Player1Healer: public Healer {
public:
    Player1Healer(int x, int y);
};

class Player1Wizard: public Wizard {
public:
    Player1Wizard(int x, int y);
};

class Player1Jew: public Jew {
public:
    Player1Jew(int x, int y);
};

class Player1Kamikadze: public Kamikadze {
public:
    Player1Kamikadze(int x, int y);
};

// юниты игрока 2

class Player2Gladiator: public Gladiator{
public:
    Player2Gladiator(int x, int y);
};

class Player2Gunslinger: public Gunslinger {
public:
    Player2Gunslinger(int x, int y);
};

class Player2Healer: public Healer {
public:
    Player2Healer(int x, int y);
};

class Player2Wizard: public Wizard {
public:
    Player2Wizard(int x, int y);
};

class Player2Jew: public Jew {
public:
    Player2Jew(int x, int y);
};

class Player2Kamikadze: public Kamikadze {
public:
    Player2Kamikadze(int x, int y);
};

/* отдел для абстрактной фабрики */

class ArmyFactory {
public:
    virtual Gladiator* createGladiator(int x, int y) = 0;
    virtual Gunslinger* createGunslinger(int x, int y) = 0;
    virtual Healer* createHealer(int x, int y) = 0;
    virtual Wizard* createWizard(int x, int y) = 0;
    virtual Jew* createJew(int x, int y) = 0;
    virtual Kamikadze* createKamikadze(int x, int y) = 0;
   // virtual ~ArmyFactory();
};

class Player1Factory: public ArmyFactory{
public:
    Gladiator * createGladiator(int x, int y);
    Gunslinger * createGunslinger(int x, int y);
    Healer * createHealer(int x, int y);
    Wizard * createWizard(int x, int y);
    Jew * createJew(int x, int y);
    Kamikadze * createKamikadze(int x, int y);
};

class Player2Factory: public ArmyFactory{
public:
    Gladiator * createGladiator(int x, int y);
    Gunslinger * createGunslinger(int x, int y);
    Healer * createHealer(int x, int y);
    Wizard * createWizard(int x, int y);
    Jew * createJew(int x, int y);
    Kamikadze * createKamikadze(int x, int y);
};

#endif // UNIT_H
