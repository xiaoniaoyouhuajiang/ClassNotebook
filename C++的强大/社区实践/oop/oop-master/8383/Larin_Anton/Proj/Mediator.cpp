//
// Created by anton on 3/2/20.
//

#include "Mediator.h"

#include "Field.h"
#include "LandscapeProxy.h"
#include "FieldCellProxy.h"
#include "Factory/CommonFactory.h"
#include "GameObjectList.h"
//#include "Observer.h"

Mediator::Mediator(int fieldWidth, int fieldHeigh) {
    field = new Field(fieldWidth, fieldHeigh, fieldWidth * fieldHeigh);
    init();
}

Mediator::Mediator(Field *field1) {
    field = field1;
    init();
}

void Mediator::init() {
    commonFactory = new CommonFactory(field);

}

void Mediator::setObserver(Observer *observer1) {
    observer = observer1;

}

void Mediator::createObserver() {
    //TODO
//observer = new Observer(this);
}

GameObjectList Mediator::getGameObjectList() {
    auto lst = GameObjectList();
    for (auto it = field->begin(); it != field->end(); it.next()) {
        lst.push_back(*it);
    }
    return lst;

}

void Mediator::getSize(int &width, int &height) {
    width = field->width;
    height = field->height;
}

GameObject *Mediator::getObjAt(int x, int y) {
    return field->getAt(x, y);
}

int Mediator::getGirdleAt(int x, int y) {
    int w = field->width, h = field->height;
    int vDist = y < h / 2 ? y + 1 : w - y;
    int hDist = x < w / 2 ? x + 1 : h - x;
    return vDist <= hDist ? vDist : hDist;
}

int Mediator::getOrdAt(int x, int y, UnitDevotion side) {
    switch (side) {
        case UnitDevotion::LIGHT:
            return y + 1;
        case UnitDevotion::DARK: {
            int h = field->height;
            return h - y;
        }
        case UnitDevotion::NEUTER:
            std::cout << "Ord cannot be counted from neuter side!!";
            assert(false);
            return -1;
    }
}

bool Mediator::createAt(UnitClass unitClass, UnitDevotion devotion, int x, int y) {

    if (field->getAt(x, y))return false;
    GameObject *unit = commonFactory->createUnit(unitClass, devotion, x, y);
    unit->setActive(true);
    field->setAt(*unit, x, y);
}


void Mediator::getGodPowers(UnitDevotion godSide, bool &allyColour, bool &enemyColour) {
    auto lst = getGameObjectList().ofType(UnitType::GOD).ofDevotion(godSide);
    allyColour = !GameObjectList(lst).ofClass(UnitClass::ALPHA).empty();
    enemyColour = !GameObjectList(lst).ofClass(UnitClass::BETA).empty();
}

void Mediator::changeGodPowers(UnitDevotion godSide, UnitDevotion powerSide, bool power) {
    auto fLst = getGameObjectList().ofType(UnitType::FIGHTER).ofDevotion(godSide);
    for (auto f:fLst) {
        if (godSide == powerSide) {
            dynamic_cast<Fighter *>(f)->setAllyPowered(power);
        } else {
            dynamic_cast<Fighter *>(f)->setEnemyPowered(power);
        }
    }
}

bool Mediator::destroyAt(int x, int y) {
    auto obj = field->removeAt(x, y);
    if (obj) {

        delete obj;
        return true;
    }
    return false;
}

Observer *Mediator::getObserver() {
    return observer;
}

bool Mediator::moveObj(int x1, int y1, int x2, int y2) {
    GameObject *src = field->getAt(x1, y1);
    GameObject *dst = field->getAt(x2, y2);
    if (src) {
        src->operator+=(getFieldCellAt(x2, y2));//First: say stepping object what it stepped at

        if (dst) {
            dst->operator-=(*src);//Then say object being stepped at
            // Or not, src obj should take care of it
            //dst->die(src);
            destroyAt(x2, y2);
        }

        src->setCoords(x2, y2);
        field->move(x1, y1, x2, y2);
        if(!src->isActive())
            destroyAt(x2, y2);
        return true;
    }
    return false;
}

LandscapeProxy Mediator::getLandscapeAt(int x, int y) {
    return LandscapeProxy(this, x, y);
}

FieldCellProxy Mediator::getFieldCellAt(int x, int y) {
    return FieldCellProxy(this, x, y);
}

UnitDevotion Mediator::getColorAt(int x, int y) {
    return (x + y) % 2 ? UnitDevotion::DARK : UnitDevotion::LIGHT;
}


