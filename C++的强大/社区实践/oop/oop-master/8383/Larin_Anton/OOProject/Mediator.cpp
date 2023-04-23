//
// Created by anton on 5/23/20.
//

#include "Mediator.h"
#include "FlyCell.h"

#include "Game.h"
#include "Exeptions/AttemptToSetNeutralBaseException.h"
#include "Exeptions/SelectionOutOfBoundsExeption.h"
#include "Exeptions/NoTerrainException.h"

const std::pair<int, int> &Mediator::getSelectionA() const {
    return selectionA;
}

void Mediator::setSelectionA(const std::pair<int, int> &selectionA) {
    if(selectionA.first<0||selectionA.first>=field->width || selectionA.second<0||selectionA.second>=field->height){
        throw SelectionOutOfBoundsExeption(selectionA,{field->width,field->height});
    }
    Mediator::selectionA = selectionA;
}

const std::pair<int, int> &Mediator::getSelectionB() const {
    return selectionB;
}

void Mediator::setSelectionB(const std::pair<int, int> &selectionB) {
    if(selectionB.first<0||selectionB.first>=field->width || selectionB.second<0||selectionB.second>=field->height){
        throw SelectionOutOfBoundsExeption(selectionB,{field->width,field->height});
    }
    Mediator::selectionB = selectionB;
}

int Mediator::distance() {
    return abs(selectionA.first-selectionB.first)+abs(selectionA.second-selectionB.second);
}

int Mediator::getSteepnessAtB() {
    return field->getTerrainAt(selectionB.first,selectionB.second)->getSteepness();
}

bool Mediator::step() {
    bool flag = true;
    auto A = field->getUnitAt(selectionA.first,selectionA.second);
    if(!A)return false;//NoUnit
    if(!(A->canStep(selectionB.first,selectionB.second)))return false;//Cant step
    auto B = field->getUnitAt(selectionB.first,selectionB.second);
    if(B)return false;//Dest occupied

    if(flag){
        auto Bt = field->getTerrainAt(selectionB.first,selectionB.second);
        if(!Bt)throw NoTerrainException(selectionB.first,selectionB.second);
        Bt->restep(A);
        if(A->canStep(selectionB.first,selectionB.second)){
            A->step(std::static_pointer_cast<GameObject>(Bt));
            //field->objSwap(selectionA.first,selectionA.second,selectionB.first,selectionB.second);
        }else flag= false;
    }

    auto Be = field->getEntityAt(selectionB.first, selectionB.second);
    if(flag) {
        if (Be) {
            Be->restep(A);
            if (A->canStep(selectionB.first, selectionB.second)) {
                A->step(Be);
            } else flag = false;
        }
    }

    if(flag&&!A->isToBeRemoved()){
        field->objSwap(selectionA.first,selectionA.second,selectionB.first,selectionB.second);
        A->setCoords(selectionB);

        logger<<("Unit from "+std::to_string(selectionA.first)+":"+std::to_string(selectionA.second) + " stepped at "+std::to_string(selectionB.first)+":"+std::to_string(selectionB.second));
    }

    A->setBlocked(false);
    if(A->isToBeRemoved()) {
        logger<<( std::string( A->getDevotion()==Devotion ::Light?"Light":(A->getDevotion()==Devotion ::Dark?"Dark":"Neuter"))+" unit at "+std::to_string(selectionA.first)+":"+std::to_string(selectionA.second) + " died");
        field->setUnitAt(std::shared_ptr<Unit>(nullptr), selectionA.first, selectionA.first);
    }
    if(Be&&Be->isToBeRemoved()) {
        logger<<("Entity at "+std::to_string(selectionB.first)+":"+std::to_string(selectionB.second) + "died");
        field->setEntityAt(std::shared_ptr<Entity>(nullptr), selectionB.first, selectionB.first);
    }

    return true;
}

bool Mediator::act() {
    bool flag = true;
    auto A = field->getUnitAt(selectionA.first,selectionA.second);
    if(!A)return false;//NoUnit
    if(!(A->canAct(selectionB.first,selectionB.second)))return false;//Cant step

    auto B = field->getUnitAt(selectionB.first,selectionB.second);
    if(B){
        A->act(B);
        B->react(A);
        A->setBlocked(false);
        B->setBlocked(false);

        logger<<("Unit from "+std::to_string(selectionA.first)+":"+std::to_string(selectionA.second) + " attacked unit at "+std::to_string(selectionB.first)+":"+std::to_string(selectionB.second));
        if(A->isToBeRemoved()){
            logger<<( std::string( A->getDevotion()==Devotion ::Light?"Light":(A->getDevotion()==Devotion ::Dark?"Dark":"Neuter"))+" unit at "+std::to_string(selectionA.first)+":"+std::to_string(selectionA.second) + " died");
            field->setUnitAt(std::shared_ptr<Unit>(nullptr),selectionA.first,selectionA.first);
        }
        if(B->isToBeRemoved()){
            logger<<( std::string( B->getDevotion()==Devotion ::Light?"Light":(B->getDevotion()==Devotion ::Dark?"Dark":"Neuter"))+" unit at "+std::to_string(selectionB.first)+":"+std::to_string(selectionB.second) + " died");
            field->setUnitAt(std::shared_ptr<Unit>(nullptr),selectionB.first,selectionB.first);
        }
        return true;

    }else{
        auto Be = field->getEntityAt(selectionB.first,selectionB.second);
        if(Be){
            //A->act(Be);
            Be+=A;
            Be->react(A);
            A->setBlocked(false);

            logger<<("Unit from "+std::to_string(selectionA.first)+":"+std::to_string(selectionA.second) + " attacked entity at "+std::to_string(selectionB.first)+":"+std::to_string(selectionB.second));
            if(A->isToBeRemoved()){
                logger<<( std::string( A->getDevotion()==Devotion ::Light?"Light":(A->getDevotion()==Devotion ::Dark?"Dark":"Neuter"))+" unit at "+std::to_string(selectionA.first)+":"+std::to_string(selectionA.second) + "died");
                field->setUnitAt(std::shared_ptr<Unit>(nullptr),selectionA.first,selectionA.first);
            }
            if(Be->isToBeRemoved()){
                logger<<("Entity at "+std::to_string(selectionB.first)+":"+std::to_string(selectionB.second) + "died");
                field->setEntityAt(std::shared_ptr<Entity>(nullptr),selectionB.first,selectionB.first);
            }

            return true;
        }else{
            return false;//Nothing to act on
        }
    }
    assert(0);
}

Mediator::Mediator(const std::shared_ptr<Field> &field, const std::shared_ptr<CommonFactory> &factory) : field(field),
                                                                                                         factory(factory) {}

bool Mediator::createObject(int x, int y, Devotion devotion, CommonClass objectClass) {
    if(x<0||x>=field->width || y<0||y>=field->height){
        throw SelectionOutOfBoundsExeption({x,y},{field->width,field->height});
    }
    if(objectClass!=CommonClass::Base) {
        switch (devotion) {
            case Devotion::Neuter:
                break;
            case Devotion::Light:
                if (factory->getLightBase()->isLim())return false;
                break;
            case Devotion::Dark:
                if (factory->getDarkBase()->isLim())return false;
                break;
        }
    }

    std::shared_ptr<GameObject> object;
    try {
        object = factory->createObject(x, y, devotion, objectClass);
    }catch(MediatorNotSetException& e){
        std::cerr<<e;
        exit(1);
    }catch(AttemptToSetNeutralBaseException& e){
        std::cerr<<e;
        exit(1);

    }
    ObjectType  ot = classToType(objectClass);
    switch (ot){

        case ObjectType::Unit:{
            auto pp = field->getUnitAt(x,y);
            if(pp)return false;
            auto cObject = std::dynamic_pointer_cast<Unit>(object);
            assert(cObject);
            field->setUnitAt(cObject,x,y);
            logger<<("Unit of class "+std::to_string(int(commonToUnit(objectClass)))+" at "+std::to_string(x)+":"+std::to_string(y)+" was spawned by "+ (devotion==Devotion::Light?"light":(devotion==Devotion::Dark?"dark":"no"))+" base");
            break;
        }
        case ObjectType::Entity:{
            auto pp = field->getEntityAt(x,y);
            if(pp)return false;
            auto cObject = std::dynamic_pointer_cast<Entity>(object);
            assert(cObject);
            field->setEntityAt(cObject,x,y);
            break;
        }
        case ObjectType::Terrain:{
            object.reset();
            auto cObject = std::make_shared<TerrainProxy>(x,y,classToTerrain(objectClass),factory);
            assert(cObject);
            field->setTerrainAt(cObject,x,y);
            break;
        }
        /*
        case ObjectType::Base:{
            auto cObject = std::static_pointer_cast<Unit>(object);
            //auto cObject = std::dynamic_pointer_cast<Unit>(object);
            assert(cObject);
            field->setUnitAt(cObject,x,y);
            break;
        }
        */
        case ObjectType::NONE:assert(0);//TODO exception creating NONE class object
    }
    return false;
}

FlyCell Mediator::getFlyCellAt(int x, int y) {
    FlyCell flyCell;
    auto uPtr = field->getUnitAt(x,y);
    flyCell.setUnit(uPtr?uPtr->getFlyWeight(): nullptr);
    //flyCell.unit = uPtr?uPtr->getFlyWeight(): nullptr;
    auto tPtr = field->getTerrainAt(x,y);
    flyCell.setTerrain(tPtr?tPtr->getFlyWeight(): nullptr);
    //flyCell.terrain=tPtr?tPtr->getFlyWeight(): nullptr;
    auto ePtr = field->getEntityAt(x,y);
    flyCell.setEntity(ePtr?ePtr->getFlyWeight(): nullptr);
    //flyCell.entity=ePtr?ePtr->getFlyWeight(): nullptr;

    if(uPtr){
        flyCell.unit->hasStats=true;
        flyCell.unit->health=uPtr->getVitality().getHealth();
    }
    if(tPtr){
        flyCell.terrain->hasStats=true;
        flyCell.terrain->health=tPtr->getVitality().getHealth();
    }
    if(ePtr){
        flyCell.entity->hasStats=true;
        flyCell.entity->health=tPtr->getVitality().getHealth();
        if(ePtr->getObjectClass()==CommonClass::Base){
            auto bPtr = std::static_pointer_cast<Base>(ePtr);
            flyCell.entity->cur=bPtr->getCur();
            flyCell.entity->lim=bPtr->getLim();
        }
    }

    return flyCell;

}

std::vector<std::vector<FlyCell>> Mediator::getFW() {//TODO not tested
    std::vector<std::vector<FlyCell>> res(field->height);

    for(int i = 0;i<field->height;i++){
        res[i]=(std::vector<FlyCell>(field->width));
    }
    for(int y = field->height-1;y>=0;y--){
        //std::vector<FlyCell> vec(field->width);
        for(int x = 0; x<field->width;x++){
            auto tmp = getFlyCellAt(x,y);
            res[y][x]=tmp;
        }
        //res.push_back(vec);
    }
    return res;
}

std::pair<int, int> Mediator::getDimensions() {
    return {field->width,field->height};
}

std::pair<int, std::pair<int, int>> Mediator::getBaseStats(Devotion devotion) {
    int h=-1;
    int c=-1;
    int l=-1;
    switch (devotion){

        case Devotion::Neuter:break;
        case Devotion::Light:{
            auto ptr = field->getEntityAt(Game::gameRules.initAPos.first,Game::gameRules.initAPos.second);
            h=ptr->getVitality().getHealth();
            auto bPtr = std::static_pointer_cast<Base>(ptr);
            c=bPtr->getCur();
            l=bPtr->getLim();
            break;
        }
        case Devotion::Dark:{
            auto ptr = field->getEntityAt(Game::gameRules.initBPos.first,Game::gameRules.initBPos.second);
            h=ptr->getVitality().getHealth();
            auto bPtr = std::static_pointer_cast<Base>(ptr);
            c=bPtr->getCur();
            l=bPtr->getLim();
            break;
        }
    }
    return {h,{c,l}};
}

void Mediator::setLogger(const std::shared_ptr<AbstractLogger> &logger) {
    Mediator::logger = logger;
}

void Mediator::onBaseDestroyed(Devotion devotion) {
    logger<<(std::string(devotion==Devotion::Light?"Dark":"Light")+" wins!");
    exit(0);
}

void Mediator::onUnitsDestroyed(Devotion devotion) {
    if(Game::gameRules.winCondition==WinCondition::UnitsDead){
        logger<<(std::string(devotion==Devotion::Light?"Dark":"Light")+" wins!");
    }
}


