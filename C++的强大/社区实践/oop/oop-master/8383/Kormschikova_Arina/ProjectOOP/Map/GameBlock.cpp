
#include "GameBlock.h"
#include "Map.h"
#include "Units.h"
#include "NeutralObject.h"
#include "Base.h"
#include <iostream>



GameBlock::GameBlock(){
    unitOnBlock = nullptr;
    baseOnBlock = nullptr;
    objectOnBlock = nullptr;
    landscape = new Grass;
}

bool GameBlock::setUnit(Unit* unit){
    if(unitOnBlock == nullptr ){
        unitOnBlock = unit;
        return 0;
    }
    return 1;
}

bool GameBlock::setBase(Base* base){
    if(baseOnBlock == nullptr){
        baseOnBlock = base;
        return 0;
    }
    return 1;
}
bool GameBlock::setObject(NeutralObject *obj){
    if(objectOnBlock == nullptr){
        objectOnBlock = obj;
        return 0;
    }
    return 1;
}


bool GameBlock::deleteUnit(){
    if(unitOnBlock){
        unitOnBlock = nullptr;
        return 0;
    }
    return 1;
}


bool GameBlock::isEmpty(){
    if(this->baseOnBlock == nullptr && this->objectOnBlock == nullptr && this->unitOnBlock == nullptr){
        if(this->landscape->type == ' '){
             return 1;
        }
        else{
            std::cout<<"inappropriate landscape"<<std::endl;
            return 0;
        }
    }
    return 0;
}

//-----------------------------------//

Water::Water(){
    this->availability = false;
    this->type = '~';
}

Forest::Forest(){
    this->type = '^';
    this->availability = true;
}

Grass::Grass(){
    this->type = ' ';
    this->availability = true;
}
