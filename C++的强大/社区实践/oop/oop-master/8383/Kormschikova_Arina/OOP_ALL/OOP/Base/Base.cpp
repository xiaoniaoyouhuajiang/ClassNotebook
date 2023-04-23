#include <iostream>
#include <sstream>
#include "Base.h"
#include "UnitsFactory.h"
#include "Units.h"

Base::Base(){
    this->hitPoint = 10;
    this->maxUnit = 4;
    this->unitsInBase = 0;
    this->type = '=';
}


Base::Base(int x, int y): Base(){
    
    this->x = x;
    this->y = y;
}


bool Base::createUnit(){
    std::stringstream messageForLog;
    Adapter adapter;
    if(unitsInBase < maxUnit){
        char type;
        std::cout<<"Enter type of unit:\n R - Ranger \n S - Slayer \n W - Witch \n B - Battle mage \n P - Paladin \n L - Lancer Knight\n Default: P"<<std::endl;
        try{
            std::cin>>type;
            messageForLog<<"\nUser input: "<<type<<std::endl;
            adapter.InfoStr(messageForLog.str());
        }
        catch(const std::istream::failure& ex){
          messageForLog <<"User input fail: "<<type<<std::endl;
          adapter.InfoStr(messageForLog.str());
          adapter.InfoErrorCode(ex.code());
          std::cin.clear();
          std::cin.ignore(10000, '\n');
          type = 'R';
        }
        
        
        return createUnit(type);
    }
    else{
        messageForLog<<"Create unit fail."<<std::endl;
        std::cout<<"too many units"<<std::endl;
        loggerP->request(new LogInfo(messageForLog.str()));
        return 1;
    }
}

bool Base::createUnit(char type){
    if(unitsInBase < maxUnit){
        std::stringstream messageForLog;
        messageForLog<<"Create unit in base ("<<this->x<<";"<<this->y<<"). ";

        switch (type) {
            case 'R':
                messageForLog<<"Rogue was created"<<std::endl;
                units.push_back(f1.createRogue());
                break;
            case 'S':
                messageForLog<<"Slayer was created"<<std::endl;
                units.push_back(f2.createRogue());
                break;
            case 'W':
                messageForLog<<"Witch was created"<<std::endl;
                units.push_back(f1.createMage());
                break;
            case 'B':
                messageForLog<<"Battle mage was created"<<std::endl;

                units.push_back(f2.createMage());
                break;
            case 'P':
                messageForLog<<"Paladin was created"<<std::endl;

                units.push_back(f2.createWarrior());
                break;
            case 'L':
                messageForLog<<"Lancer Knight was created"<<std::endl;

                units.push_back(f1.createWarrior());
                break;
            default:
                messageForLog<<"Paladin was created"<<std::endl;

                units.push_back(f2.createWarrior());
                break;
        }
        loggerP->request(new LogInfo(messageForLog.str()));
        units.back()->setLog(loggerP);
        unitsInBase++;
        return 0;
    }
    else{
        return 1;
    }

}


void Base::showStat(){
    std::cout<<"\nBase HP:"<<this->hitPoint<<"\n\nUnits in base:"<<units.size()<<std::endl;
    int i = 1;
    for(auto iter = units.begin(); iter != units.end(); iter++){
        std::cout<<i++<<std::endl;
        (*iter)->showStat();
        std::cout<<std::endl;
    }
    std::cout<<"Count of units defined to this base:"<<this->unitsInBase<<std::endl;
}


Unit* Base::getUnit(){
    std::stringstream messageForLog;
    int k;
    Adapter* a = new Adapter;
    if(units.size() == 0){
        std::cout<<"There are no units in base"<<std::endl;
        messageForLog<<"Getting unit fail - no units in base"<<std::endl;
        a->InfoStr(messageForLog.str());
        return nullptr;
    }
    this->showStat();
    do{
    std::cout<<"Enter number:"<<std::endl;
        
    try {
        std::cin>>k;
        messageForLog<<"User input: "<<k<<std::endl;
        a->InfoStr(messageForLog.str());
    } catch (const std::istream::failure& ex) {
        
        std::cout<<"Wrong input!"<<std::endl;
        messageForLog<<"Wrong input: "<<k<<std::endl;
        a->InfoStr(messageForLog.str());
        a->InfoErrorCode(ex.code());
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        k = 0;
    }
        
    

    }while(k  > units.size() || k < 1);
    auto iter = units.begin();
    std::advance(iter, k-1);
    Unit* u = *iter;
    units.erase(iter);
    return u;
}



void Base::updateU(){
    for(auto iter = units.begin(); iter != units.end(); iter++){
        (*iter)->update();
    }
}

void Base::baseUpdate(){
   for(auto iter = units.begin(); iter != units.end(); iter++){
       if( (*iter)->hitPoint < 0){
            units.erase(iter);
           unitsInBase--;
        }
    }
}

void Base::setLog(LogProxy *logger){
    this->loggerP = logger;
}

std::ostream& operator <<(std::ostream& os, const Base& base){
    os<<base.x<<" "<<base.y<<" "<<base.hitPoint<<" "<<base.maxUnit<<" "<<base.unitsInBase<<" "<<base.units.size()<<std::endl;
    for(int i = 0; i < base.units.size(); i++){
        os<<*(base.units[i]);
    }
    return os;
}

void Base::getDamage(int damage){
    
    std::stringstream messageForLog;

    this->hitPoint -= damage;
    if (hitPoint<1){
        std::cout<<"Base  get damage "<<damage<<" and destroyed"<<std::endl;
        messageForLog<<"Unit "<<this->type<<" get damage "<<damage<<" and destroyed"<<std::endl;
    }
    else{
        std::cout<<"Base get damage. "<<damage<<" HP:"<<this->hitPoint<<std::endl;
        messageForLog<<"Base get damage. "<<damage<<" HP:"<<this->hitPoint<<std::endl;
    }
    if(loggerP->getType() != CONSOLE){
        loggerP->request(new LogInfo(messageForLog.str()));
    }
}
