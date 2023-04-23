#include <iostream>
#include <string>
using namespace std;
#pragma once
#include <component.h>

class Base : public IObserver{
    Field *field;
protected:
    ConcreteFactoryDragon concreteFactoryDragon;
    ConcreteFactoryWarrior concreteFactoryWarrior;
    ConcreteFactorySentry concreteFactorySentry;
    Component *units;
    Adapter *adapter;
    //Mediator *mediator;
    unsigned int width = 5;
    unsigned int height = 5;
    int max_item = 5;
    int now_item = 0;
    int health = 0;
    string who = "BAS";

public:

    Base(Field *obj, Adapter* adapter) : field(obj), adapter(adapter){
            health = 2000;
            //mediator = new Mediator;
            units = new Composite;
            units->Add(new Composite);
            units->Add(new Composite);
            units->Add(new Composite);
            for (unsigned i=0; i<3; i++)
            {
                units->getChildren(i)->Add(new Leaf);
                units->getChildren(i)->Add(new Leaf);
            }
        }

    Component* get_comp(){
        return  units;
    }

    int getHealth()
    {
        return health;
    }

    void setHealth(int value)
    {
        health = value;
    }

    string print_who(){
        return who;
    }

    string print_units_whoami() {
            return units->getUnits_WhoAmI();
    }

    Item* copy()
    {
        Base* base = new Base(field, adapter);
        return base;
    }

    void add_info(unsigned int x, unsigned int y, string &logs, string s_unit){
        //logs += units->getUnits_WhoAmI() + "\n";
        logs += s_unit;
        field->get_unit(x, y, logs);
        now_item++;
    }
    int getAttack(){}
    int get_nearAttack(){}
    int get_furtherAttack(){}
    virtual void operator+= (Item* bonus){}

    void add_green_dr(unsigned int x, unsigned int y, string &logs){
        if (now_item < max_item){
            Unit* dragon = concreteFactoryDragon.CreateUnitB(this);
            //dragon->setHealth(1000);
            if (field->add_item(x, y, dragon, logs)){
                dragon->set_mediator(field->get_mediator());
                units->getChildren(0)->getChildren(1)->addUnit(dragon);
                add_info(x, y, logs, "Add green dragon: ");
            }
        }
        else {
            logs += adapter->print("Maximum number of units!\n");
        }
    }

    void add_red_dr(unsigned int x, unsigned int y, string &logs){
        if (now_item < max_item){
            Unit* dragon = concreteFactoryDragon.CreateUnitA(this);
            if (field->add_item(x, y, dragon, logs)){
                dragon->set_mediator(field->get_mediator());
                units->getChildren(0)->getChildren(0)->addUnit(dragon);
                add_info(x, y, logs, "Add red dragon: ");
            }
        }
        else {
            logs += adapter->print("Maximum number of units!\n");
        }
    }

    void add_war_fight(unsigned int x, unsigned int y, string &logs){
        if (now_item < max_item){
            Unit* fight = concreteFactoryWarrior.CreateUnitA(this);
            //fight->setHealth(1000);
            if (field->add_item(x, y, fight, logs)){
                fight->set_mediator(field->get_mediator());
                units->getChildren(1)->getChildren(0)->addUnit(fight);
                add_info(x, y, logs, "Add warrior fight: ");
            }
        }
        else {
            logs += adapter->print("Maximum number of units!\n");
        }
    }

    void add_war_ronin(unsigned int x, unsigned int y, string &logs){
        if (now_item < max_item){
            Unit* ronin = concreteFactoryWarrior.CreateUnitB(this);
            //ronin->setHealth(1000);
            if (field->add_item(x, y, ronin, logs)){
                ronin->set_mediator(field->get_mediator());
                units->getChildren(1)->getChildren(1)->addUnit(ronin);
                add_info(x, y, logs, "Add warrior ronin: ");
            }
        }
        else {
            logs += adapter->print("Maximum number of units!\n");
        }
    }

    void add_sen_fire(unsigned int x, unsigned int y, string &logs){
        if (now_item < max_item){
            Unit* fire = concreteFactorySentry.CreateUnitA(this);
            //fire->setHealth(1000);
            if (field->add_item(x, y, fire, logs)){
                fire->set_mediator(field->get_mediator());
                units->getChildren(2)->getChildren(0)->addUnit(fire);
                add_info(x, y, logs, "Add sentry fire: ");
            }
        }
        else {
            logs += adapter->print("Maximum number of units!\n");
        }
    }

    void add_sen_lion(unsigned int x, unsigned int y, string &logs){
        if (now_item < max_item){
            Unit* lion = concreteFactorySentry.CreateUnitB(this);
            if (field->add_item(x, y, lion, logs)){
                lion->set_mediator(field->get_mediator());
                units->getChildren(2)->getChildren(1)->addUnit(lion);
                add_info(x, y, logs, "Add sentry lion: ");
            }
        }
        else {
            logs += adapter->print("Maximum number of units!\n");
        }
    }

    void delete_unit(Item* obj){
        if (obj->print_who() == "D_R") {
            units->getChildren(0)->getChildren(0)->removeUnit(obj);
        }
        else if (obj->print_who() == "D_G") {
            units->getChildren(0)->getChildren(1)->removeUnit(obj);
        }
        else if (obj->print_who() == "W_F") {
            units->getChildren(1)->getChildren(0)->removeUnit(obj);
        }
        else if (obj->print_who() == "W_R") {
            units->getChildren(1)->getChildren(1)->removeUnit(obj);
        }
        else if (obj->print_who() == "S_F") {
            units->getChildren(2)->getChildren(0)->removeUnit(obj);
        }
        else if (obj->print_who() == "S_L") {
            units->getChildren(2)->getChildren(1)->removeUnit(obj);
        }
        now_item--;
        //cout << "Del";
    }

};
