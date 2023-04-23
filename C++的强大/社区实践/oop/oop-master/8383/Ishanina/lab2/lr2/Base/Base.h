//
// Created by Mila
//

#ifndef UNTITLED_BASE_H
#define UNTITLED_BASE_H


#include "../Units/ObjectInterface.h"
#include "../AbstractFactory/AbstractFactory.h"
#include "../AbstractFactory/ConcreteFactoryMagicHero.h"
#include "../AbstractFactory/ConcreteFactoryStrongHero.h"
#include "../Field/Field.h"
#include "../Observer/Observer.h"
#include <vector>

class Base : public ObjectInterface, public Observer{
private:
    ConcreteFactoryMagicHero* fMagic;
    ConcreteFactoryStrongHero* fStrong;
    Field* field;
    int counter;//номер базы
    Unit** units;
    int countUnit;
    int controlMax;//максимальное количество юнитов
    int health;//здоровье
public:

    Base(Field* field, Unit** units, int counter, int controlMax);
    int getCountUnit() const;
    char whatYouName() override;
    ObjectInterface* copy() override;
    void createUnit(int type, int x, int y);
    void handleEvent(unsigned numberInArray) override;


};


#endif //UNTITLED_BASE_H
