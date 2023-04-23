//
// Created by anton on 2/12/20.
//



#include "Alpha.h"

//#include "../Mediator.h"

#include "../LandscapeProxy.h"
#include "../FieldCellProxy.h"

UnitClass Alpha::getUnitClass() const {
    return UnitClass::ALPHA;
}

void Alpha::deathEvent() {
    //God::deathEvent();//TODO
}

void Alpha::summon(Direction dir) {
    //God::summon(dir);//TODO
}

wchar_t Alpha::toChar() {
    //return L'α';
    return L'a';

}

bool Alpha::isValidStep(int x, int y) {
    return true;
}

bool Alpha::step(int x, int y) {
    /*
    if(isValidStep(x,y)){
        int mx,my;getCoords(mx,my);
        if(GameObject::mediator->moveObj(mx,my,x,y)){
            return  true;
        }
    }
     */
    return false;
}

Alpha::Alpha(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active) : God(fld, x, y, health,
                                                                                             devotion,
                                                                                             active) {
    addObserver(this);
    unitCnt = 0;
}

GameObject &Alpha::operator+=(const LandscapeProxy &b) {
    return *this;
}

int Alpha::getUnitLim() {
    return unitLim;
}

void Alpha::setUnitLim(int unitLim1) {
    unitLim = unitLim1;
}

bool Alpha::spawnAt(UnitClass unitClass, int x, int y) {

    if(unitCnt<unitLim){
        bool erfolg = GameObject::mediator->createAt(unitClass, this->getUnitDevotion(), x, y);
        if (erfolg) {
            GameObject *go = mediator->getObjAt(x, y);
            go->addObserver(this);
        }

        return erfolg;
        //observer->notifyCreate(g);

    }
    return false;
}

GameObject &Alpha::operator+=(const FieldCellProxy &b) {
    auto j = b.getLandscape();
    this->operator+=(b.getLandscape());
    kill(*this, *b.getObject());
    //sigKill(*this,*b.getObject());
    return *this;
}

GameObject &Alpha::operator-=(const GameObject &b) {
    return *this;
}

void Alpha::slKill(GameObject &src, GameObject &dst) const {
    std::cout << "Class " << (int) src.getUnitClass() << " killed class " << (int) src.getUnitClass() << std::endl;
}

void Alpha::slDeath(const GameObject &src, GameObject &dst) const {
    std::cout << "Class " << (int) dst.getUnitClass() << " was killed by class " << (int) src.getUnitClass()
              << std::endl;
    //if(dst.getUnitDevotion()==getUnitDevotion())unitCnt--;
}



/*void Alpha::recieveDeath(GameObject *gameObject) {
    unitCnt--;
    std::cout<<"Oh no, someone died"<<std::endl;

}*/

//Alpha::Alpha(Field *fld, int x, int y, int health, UnitDevotion devotion, bool active,             CommonFactory *factory, int unitLim) : God(fld, x, y, health, devotion, active),                                                    Base(fld, factory, unitLim) {}

