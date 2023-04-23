#include <iostream>
#include <sstream>

#include "Units.h"
#include "Base.h"
#include "Map.h"
#include "GameBlock.h"
#include "NeutralObject.h"
#include "Exeptions.h"


void Unit::showStat(){
    std::cout<<type<<std::endl<<"HP:"<<hitPoint<<std::endl<<"MP:"<<manaPoint<<std::endl<<"Magic resist:"<<magicResistance<<std::endl<<"Armor:"<<armor<<std::endl;
}

bool Unit::move(int x, int y, GameMap& map){
    
    int oldX = this->x;//log
    int oldY = this->y;
    Adapter* a = new Adapter;
    GameBlock* nextBlock = nullptr;
    if((map.getHeight() > (this->y+y)) && (map.getWidth() > (this->x+x)) && ((this->y+y) >= 0) && ((this->x+x) >= 0) ){
        try{
             nextBlock = map.getBlock(this->y+y, this->x+x);
        }
        catch(BlockAccessException& ex){
            Adapter a;
            a.InfoStr(ex.message());
            return false;
        }
        
        if(nextBlock->landscape->availability == false || nextBlock->unitOnBlock !=nullptr){
            std::cout<<"The passage is blocked"<<std::endl;
            a->InfoMove(this, oldX, oldY);
            delete a;
            return false;
        }
        else{
            if(nextBlock->objectOnBlock != nullptr){
                *(nextBlock->objectOnBlock) += *this;
            }
            nextBlock->setUnit(this);
            map.getBlock(this->y, this->x)->deleteUnit();
            this->x += x;
            this->y += y;
            a->InfoMove(this, oldX, oldY);
            delete a;
            return true;
        }
    }
    else{
        std::cout<<"The passage is blocked"<<std::endl;
        a->InfoMove(this, oldX, oldY);
        delete a;
        return false;
    }
    
}

void Unit::getDamage(int damage){
    
    this->hitPoint -= damage;
    if (hitPoint<1){
        std::cout<<"Unit "<<this->type<<" get damage "<<damage<<" and die"<<std::endl;
    }
    else{
        std::cout<<"Unit "<<this->type<<" get damage. "<<damage<<" HP:"<<this->hitPoint<<std::endl;
    }
}

void Unit::death(){
    delete this;
}


void Unit::update(){
    
}


bool Unit::checkForAttack(int x, int y){
    if ((x - this->x)*(x - this->x) + (y- this->y)*(y- this->y) <= (this->weapon->radius*this->weapon->radius)){
        return true;
    }
    return false;
}

void Unit::attack(Unit *enemy){
    int distanse = (enemy->x - this->x)*(enemy->x - this->x) + (enemy->y- this->y)*(enemy->y- this->y);
    int damage = this->weapon->useWeapon(distanse, enemy->magicResistance, enemy->armor);
    enemy->getDamage(damage);
    
    Adapter* a = new Adapter;
    a->InfoAttack(this, enemy, damage);
    delete a;
}

void Unit::attack(Base* enemy){
    int distanse = (enemy->x - this->x)*(enemy->x - this->x) + (enemy->y- this->y)*(enemy->y- this->y);
    int damage = this->weapon->useWeapon(distanse, 50, 90); 
    enemy->getDamage(damage);
    
    Adapter* a = new Adapter;
    a->InfoAttack(this, enemy, damage);
    delete a;
}


void Unit::setLog(LogProxy *logger){
    this->loggerP = logger;
}
//----------------------------------------//

Rogue::Rogue(){
    this->hitPoint = 100;
    this->manaPoint = 20;
}

void Rogue::update(){
    Adapter* a = new Adapter;
    a->InfoStr("RUp");
    delete a;
    
    
    
    //std::cout<<"RUp"<<std::endl;
}

Ranger::Ranger(){
    this->magicResistance = 35;
    this->armor = 25;
    this->weapon = new Bow;
    this->type = 'R';
}


Slayer::Slayer(){
    this->magicResistance = 25;
    this->armor = 35;
    this->weapon = new Dagger;
    this->type = 'S';
}

//----------------------------------------------//
Mage::Mage(){
    this->hitPoint = 100;
    this->manaPoint = 100;
}

void Mage::update(){
    
    Adapter* a = new Adapter;
    a->InfoStr("MUp");
    delete a;
       
    
    
}


BattleMage::BattleMage(){
    this->magicResistance = 40;
    this->armor = 35;
    this->weapon = new Hands;
    this->type = 'B';
}


Witch::Witch(){
    this->magicResistance = 60;
    this->armor = 10;
    this->weapon = new Staff;
    this->type = 'W';
}

//----------------------------//

Warrior:: Warrior(){
   this->hitPoint = 100;
   this->manaPoint = 10;
}


void Warrior::update(){
     Adapter* a = new Adapter;
       a->InfoStr("WUp");
       delete a;
          
}


Paladin::Paladin(){
    this->magicResistance = 25;
    this->armor = 65;
    this->weapon = new Sword;
    this->type = 'P';
}


LanceKnight::LanceKnight(){
    this->magicResistance = 35;
    this->armor = 45;
    this->weapon = new Lance;
    this->type = 'L';
}
std::ostream& operator <<(std::ostream& os, const Unit& unit){
    os<<unit.isNPC<<" "<<unit.x<<" "<<unit.y<<" "<<unit.hitPoint<<" "<<unit.manaPoint<<" "<<unit.magicResistance<<" "<<unit.armor<<" "<<unit.type<<std::endl;
    return os;
}
