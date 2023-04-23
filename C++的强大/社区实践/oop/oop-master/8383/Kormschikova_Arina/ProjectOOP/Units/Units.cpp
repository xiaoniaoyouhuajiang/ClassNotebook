#include <iostream>

#include "Units.h"
#include "Map.h"
#include "GameBlock.h"
#include "NeutralObject.h"


Unit::Unit(){
    //    this->name = 'u';
}


void Unit::showStat(){
    std::cout<<type<<std::endl<<"HP:"<<hitPoint<<std::endl<<"MP:"<<manaPoint<<std::endl<<"Magic resist:"<<magicResistance<<std::endl<<"Armor:"<<armor<<std::endl;
}

void Unit::move(int x, int y, GameMap& map){
    if((map.getHeight() > (this->y+y)) && (map.getWidth() > (this->x+x)) && ((this->y+y) >= 0) && ((this->x+x) >= 0) ){
        GameBlock* nextBlock =map.getBlock(this->y+y, this->x+x);
        if(nextBlock->landscape->availability == false){
            std::cout<<"The passage is blocked"<<std::endl;
        }
        else{
            if(nextBlock->objectOnBlock != nullptr){
                *(nextBlock->objectOnBlock) += *this;
            }
            nextBlock->setUnit(this);
            map.getBlock(this->y, this->x)->deleteUnit();
            this->x += x;
            this->y += y;
        }
    }
    else{
        std::cout<<"The passage is blocked"<<std::endl;
    }
}

void Unit::getDamage(int damage){
    //вообще тут еще нужно как-то сделать реакцию на то, что юнит сдох и в базе убрать его из списка велллл
    this->hitPoint -= damage;
    if (hitPoint<1){
        this->death();
        std::cout<<"Unit "<<this->type<<" get damage and die"<<std::endl;
    }
    else{
        std::cout<<"Unit "<<this->type<<" get damage. HP:"<<this->hitPoint<<std::endl;
    }
}

void Unit::death(){
    delete this;
}
void Unit::update(){
    
}
//----------------------------------------//

Rogue::Rogue(){
    this->hitPoint = 100;
    this->manaPoint = 20;
}

void Rogue::update(){
    std::cout<<"RUp"<<std::endl;
}

Ranger::Ranger(){
    Bow weapon;
    this->magicResistance = 35;
    this->armor = 25;
    this->weapon = weapon;
    this->type = 'R';
}


Slayer::Slayer(){
    Dagger weapon;
    this->magicResistance = 25;
    this->armor = 35;
    this->weapon = weapon;
    this->type = 'S';
}

//----------------------------------------------//
Mage::Mage(){
    this->hitPoint = 100;
    this->manaPoint = 100;
}

void Mage::update(){
    std::cout<<"MUp"<<std::endl;
}


BattleMage::BattleMage(){
    Dagger weapon;
    this->magicResistance = 40;
    this->armor = 35;
    this->weapon = weapon;
    this->type = 'B';
}


Witch::Witch(){
    Dagger weapon;
    this->magicResistance = 60;
    this->armor = 10;
    this->weapon = weapon;
    this->type = 'W';
}

//----------------------------//

Warrior:: Warrior(){
   this->hitPoint = 100;
   this->manaPoint = 10;
}


void Warrior::update(){
    std::cout<<"WUp"<<std::endl;
}


Paladin::Paladin(){
    Dagger weapon;
    this->magicResistance = 25;
    this->armor = 65;
    this->weapon = weapon;
    this->type = 'P';
}


LanceKnight::LanceKnight(){
    Dagger weapon;
    this->magicResistance = 35;
    this->armor = 45;
    this->weapon = weapon;
    this->type = 'L';
}
