#include "base.h"

Base::Base() : maxCount(6), curCount(0) {
    symb = ":/pics/base1.jpg";
}

Base::Base(int x, int y, bool numbase) : maxCount(6), curCount(0), numBase(numbase)
{
    baseCell = new Cell();
    this->baseCell->x = x;
    this->baseCell->y = y;
    this->baseCell->innerObject = this;

    if(numbase == 0){ symb = ":/pics/base1.jpg";
    }else if(numbase == 1){ symb = ":/pics/base2.jpg";}
    this->notify("Base created");
}

Base::~Base() {}


Unit* Base::createUnit(std::string str) {
    if(curCount < maxCount){
        objectFabric fabric;
        Unit* object;
        int num = this->numBase;
        if(str=="Archer"){
            object = fabric.createArcher(num);
            units.push_back(object);
        }
        else if(str=="CrossBowMan"){
            object = fabric.createCrossbowman(num);
            units.push_back(object);
        }
        else if(str=="HeavyRider"){
            object = fabric.createHeavyRider(num);
            units.push_back(object);
        }
        else if(str=="LightRider"){
            object = fabric.createLightRider(num);
            units.push_back(object);
        }
        else if(str=="Knight"){
            object = fabric.createKnight(num);
            units.push_back(object);
        }
        else if(str=="Spearman"){
            object = fabric.createSpearman(num);
            units.push_back(object);
        }
        else{
            return nullptr;
            //exception
        }
        curCount++;
        notify(str + " Unit created");
        return  object;
    }
}


void Base::attachObserver(IObserver* observer) {
    std::list<Unit*>::iterator iterator = units.begin();
    while (iterator != units.end()) {
        (*iterator)->attachObserver(observer);
        ++iterator;
    }
}

void Base::detachObserver(IObserver* observer) {
    std::list<Unit*>::iterator iterator = units.begin();
    while (iterator != units.end()) {
        (*iterator)->detachObserver(observer);
        ++iterator;
    }
}

void Base::notify(std::string message) {
    std::list<Unit*>::iterator iterator = units.begin();
    while (iterator != units.end()) {
        (*iterator)->notify(message);
        ++iterator;
    }
}
