#include <string>
#include <iostream>
#include <battle.h>
#include <land.h>
#include <strategy.h>
using namespace std;

class Item{
public:
    virtual ~Item() = default;
    virtual string print_who() = 0;
    virtual int getHealth() = 0;
    virtual int getAttack() = 0;
    virtual int get_nearAttack() = 0;
    virtual int get_furtherAttack() = 0;
    virtual void setHealth(int value) = 0;
    virtual Item* copy() = 0;
    virtual void operator+= (Item* bonus) = 0;
};

class Neutral : public Item{
protected:
    int number = 0;

public:
    virtual void take_obj() = 0;
};

class Bonus : public Neutral{
protected:
    string who = "B";
    int health = 0;
    int attack = 0; //Атака

public:
    int getHealth(){
        return health;
    }
    int getAttack(){
        return attack;
    }
    string print_who(){
        return who;
    }
    int getNumber(){
        return number;
    }
    void setHealth(int value){}
    int get_nearAttack(){}
    int get_furtherAttack(){}
    void operator+= (Item* bonus){}
};

class Bonus_health : public Bonus{
public:
    Bonus_health(){
        number = 1;
        health = 2000;
    }

    void take_obj(){
        number--;
    }
    Item* copy(){
        Item* bonus = new Bonus_health();
        return bonus;
    }
};

class Bonus_attack : public Bonus{
public:
    Bonus_attack(){
        number = 1;
        attack = 500;
    }
    void take_obj(){
        number--;
    }
    Item* copy(){
        Item* bonus = new Bonus_health();
        return bonus;
    }
};

class Bonus_all : public Bonus{
public:
    Bonus_all(){
        number = 1;
        health = 1000;
        attack = 500;
    }
    void take_obj(){
        number--;
    }
    Item* copy(){
        Item* bonus = new Bonus_health();
        return bonus;
    }
};

class Fence : public Neutral{
protected:
    string who = "";
    int health = 0;
public:
    Fence(){
        who = "#";
        health = 1000;
    }
    string print_who(){
        return who;
    }
    int getHealth(){
        return health;
    }
    void setHealth(int value){
        health = health - value;
    }
    void take_obj(){}
    int getAttack(){}
    int get_nearAttack(){}
    int get_furtherAttack(){}
    void operator+= (Item* bonus){}
    Item* copy(){
        Fence* fence = new Fence;
        return fence;
    }
};

class Unit;
class IMediator{
public:
    virtual void add_unit(Unit* unit) = 0;
    virtual int attack_unit(Item* attack_from, Item* attack_to) = 0;
};

class IObserver : public Item{
public:
    virtual void delete_unit(Item* obj) = 0;

};

class Unit: public Item{
protected:
    string who = "";
    int health = 0;
    IMediator *mediator;
    IObserver *observer;
    Battle near_battle;
    Battle further_battle;

public:

    virtual ~Unit(){
        observer->delete_unit(this);
    }

    virtual void set_mediator(IMediator* mediator){
        this->mediator = mediator;
        this->mediator->add_unit(this);
    }

    virtual void setHealth(int value)
    {
        health = health - value;
    }

    virtual int getHealth()
    {
        return health;
    }

    virtual string print_who(){
        return who;
    }
    int getAttack(){}
    int get_nearAttack(){
        return near_battle.get_attack();
    }
    int get_furtherAttack(){
        return further_battle.get_attack();
    }
    virtual Item* copy() = 0;

    void operator+= (Item* bonus){
        Strategy* strategy = new Strategy_selector(bonus->getHealth());
        health += strategy->get_bonus(this->print_who());
        near_battle.add_attack(bonus->getAttack());
        further_battle.add_attack(bonus->getAttack());
    }

};

class Dragons : public Unit{

};

class Warrior : public Unit{

};

class Sentry : public Unit{

};

class Dragons_red : public Dragons{

public:
    Dragons_red(IObserver *observer){
        who = "D_R";
        health = 2000;
        Battle near_battle(10, 220, 217, 1000);
        this->near_battle = near_battle;
        Battle further_battle(5, 2000, 217, 800);
        this->further_battle = further_battle;
        this->observer = observer;
    }

    Item* copy(){
        Dragons_red* dragon_red = new Dragons_red(observer);
        return dragon_red;
    }

};

class Dragons_green : public Dragons{

public:
    Dragons_green(IObserver *observer){
        who = "D_G";
        health = 4300;
        Battle near_battle(10, 235, 168, 1000);
        this->near_battle = near_battle;
        Battle further_battle(5, 1970, 219, 1200);
        this->further_battle = further_battle;
        this->observer = observer;
    }

    Item* copy(){
        Dragons_green* dragon_green = new Dragons_green(observer);
        return dragon_green;
    }
};

class Warrior_fight : public Warrior{

public:
    Warrior_fight(IObserver *observer){
        who = "W_F";
        health = 4300;
        Battle near_battle(10, 235, 168, 1000);
        this->near_battle = near_battle;
        Battle further_battle(25, 1970, 219, 1200);
        this->further_battle = further_battle;
        this->observer = observer;
    }

    Item* copy(){
        Warrior_fight* warrior_fight = new Warrior_fight(observer);
        return warrior_fight;
    }

};

class Warrior_ronin : public Warrior{

public:
    Warrior_ronin(IObserver *observer){
        who = "W_R";
        health = 2700;
        Battle near_battle(4, 2420, 249, 650);
        this->near_battle = near_battle;
        Battle further_battle(10, 300, 188, 650);
        this->further_battle = further_battle;
        this->observer = observer;
    }

    Item* copy(){
        Warrior_ronin* warrior_ronin = new Warrior_ronin(observer);
        return warrior_ronin;
    }

};

class Sentry_fire : public Sentry{

public:
    Sentry_fire(IObserver *observer){
        who = "S_F";
        health = 2100;
        Battle near_battle(6, 1820, 249, 1000);
        this->near_battle = near_battle;
        Battle further_battle(10, 5200, 188, 1000);
        this->further_battle = further_battle;
        this->observer = observer;
    }

    Item* copy(){
        Sentry_fire* sentry_fire = new Sentry_fire(observer);
        return sentry_fire;
    }
};

class Sentry_lion : public Sentry{

public:
    Sentry_lion(IObserver *observer){
        who = "S_L";
        health = 2700;
        Battle near_battle(8, 2680, 249, 1650);
        this->near_battle = near_battle;
        Battle further_battle(12, 4800, 188, 1650);
        this->further_battle = further_battle;
        this->observer = observer;
    }

    Item* copy(){
        Sentry_lion* sentry_lion = new Sentry_lion(observer);
        return sentry_lion;
    }
};
