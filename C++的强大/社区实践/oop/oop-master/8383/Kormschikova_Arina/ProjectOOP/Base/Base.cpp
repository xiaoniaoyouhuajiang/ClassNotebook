#include "Base.h"
#include <iostream>
#include "UnitsFactory.h"



Base::Base(){
    this->hitPoint = 50;
    this->maxUnit = 4;
    this->unitsInBase = 0;
    this->type = '=';
}
Base::Base(int x, int y): Base(){
    this->x = x;
    this->y = y;
}
bool Base::createUnit(){
    if(units.size() < maxUnit){
        char type;
        std::cout<<"Enter type of unit:\n R - Ranger \n S - Slayer \n W - Witch \n B - Battle mage \n P - Paladin \n L - Lancer Knight\n Default: P"<<std::endl;
        std::cin>>type;
        createUnit(type);
//        switch (type) {
//            case 'R':
//                units.push_back(f1.createRogue());
//                break;
//            case 'S':
//                units.push_back(f2.createRogue());
//                break;
//            case 'W':
//                units.push_back(f1.createMage());
//                break;
//            case 'B':
//                units.push_back(f2.createMage());
//                break;
//            case 'P':
//                units.push_back(f2.createWarrior());
//                break;
//            case 'L':
//                units.push_back(f1.createWarrior());
//                break;
//            default:
//                units.push_back(f2.createWarrior());
//                break;
//        }
//
//        unitsInBase++;
        return 0;
    }
    else{
        std::cout<<"too many units"<<std::endl;
        return 1;
    }
}

bool Base::createUnit(char type){
    if(units.size() < maxUnit){
        switch (type) {
            case 'R':
                units.push_back(f1.createRogue());
                break;
            case 'S':
                units.push_back(f2.createRogue());
                break;
            case 'W':
                units.push_back(f1.createMage());
                break;
            case 'B':
                units.push_back(f2.createMage());
                break;
            case 'P':
                units.push_back(f2.createWarrior());
                break;
            case 'L':
                units.push_back(f1.createWarrior());
                break;
            default:
                units.push_back(f2.createWarrior());
                break;
        }
        unitsInBase++;
        return 0;
    }
    else{
        return 1;
    }

}


void Base::showStat(){
    std::cout<<"\nBase HP:"<<this->hitPoint<<"\n\nUnits in base:"<<this->unitsInBase<<std::endl;
    int i = 1;
    for(auto iter = units.begin(); iter != units.end(); iter++){
        std::cout<<i++<<std::endl;
        (*iter)->showStat();
        std::cout<<std::endl;
    }
    std::cout<<"Count of units defined to this base:"<<units.size()<<std::endl;
}

Unit* Base::getUnit(){
    int k;
    if(units.size() == 0){
        std::cout<<"There are no units in base"<<std::endl;
        return nullptr;
    }
    this->showStat();
    do{
    std::cout<<"Enter number:"<<std::endl;
    std::cin>>k;
    }while(k  > units.size() || k < 1);
    auto iter = units.begin();
    std::advance(iter, k-1);
    return *iter;
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

