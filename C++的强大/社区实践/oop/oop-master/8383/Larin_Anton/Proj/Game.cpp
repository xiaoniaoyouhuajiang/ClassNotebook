//
// Created by anton on 2/11/20.
//

#include "Game.h"

//#include "GameObject.h"
Mediator *GameObject::mediator;//TODO MASSIVE CRUTCH HERE


Game::Game(int fieldWidth, int fieldHeight) {
    field = new Field(fieldWidth, fieldHeight, fieldHeight * fieldWidth);
    //factory = new CommonFactory(field);

    mediator = new Mediator(field);
    GameObject::mediator = mediator;
}

void Game::run() {

    mediator->createAt(UnitClass::ALPHA, UnitDevotion::LIGHT, 6, 6);

    dynamic_cast<Alpha *>(mediator->getObjAt(6, 6))->setUnitLim(field->getSize().first * field->getSize().second);


    mediator->createAt(UnitClass::ALPHA, UnitDevotion::DARK, 1, 1);

    dynamic_cast<Alpha *>(mediator->getObjAt(1, 1))->setUnitLim(field->getSize().first * field->getSize().second);



    std::cout << "1. Tho bases are set." << std::endl;
    std::wcout << field->toWString();

    //mediator.

    auto obj = mediator->getObjAt(6, 6);
    dynamic_cast<Alpha *>(obj)->spawnAt(UnitClass::GAMMA, 5, 6);

    obj = mediator->getObjAt(1, 1);
    dynamic_cast<Alpha *>(obj)->spawnAt(UnitClass::EPSILON, 2, 2);

    Epsilon* eps = dynamic_cast<Epsilon *>(mediator->getObjAt(2, 2));

    mediator->createAt(UnitClass::FIRE, UnitDevotion::NEUTER, 4, 4);

    std::cout << "2. One sets Gamma, another Epsilon. Fire appeared all by itself" << std::endl;
    std::wcout << field->toWString();



    assert(eps);


    std::cout<<"Epsilons power(ord) is "<<eps->getPower()<<std::endl;


    std::cout<<"3. Move Gamma to fire. Move Epsilon up"<<std::endl;
    mediator->moveObj(2,2,2,4);//Epsilon to 2 4
    mediator->moveObj(5,6,4,4);//Gamma to 4,4

    std::cout<<"Epsilons new power (due to landscape change): "<<eps->getPower()<<std::endl;
    std::wcout << field->toWString();






    /*


    mediator->createAt(UnitClass::STONE, UnitDevotion::NEUTER, 6, 6);
    std::wcout << field->toWString();

    mediator->moveObj(5, 5, 1, 1);

    std::wcout << field->toWString();

    std::cout << (int) (obj->getUnitClass()) << std::endl;
     */
    return;
    /*
    std::cout << "Move unit" << std::endl;
    field->move(5, 5, 7, 7);
    std::wcout << field->toWString();


    std::cout << "reset" << std::endl;
    field->resetField();
    std::wcout << field->toWString();


    std::cout << "Set unit" << std::endl;
    go = factory->createUnit(UnitClass::ALPHA);
//    objVector.push_back(go);
    field->setAt(*go, 5, 5);
    std::wcout << field->toWString();

    std::cout << "Set unit" << std::endl;
    go = factory->createUnit(UnitClass::BETA);
//    objVector.push_back(go);
    field->setAt(*go, 1, 1);
    std::wcout << field->toWString();

    std::cout << "Cut unit" << std::endl;
    field->move(1, 1, 5, 5);
    std::wcout << field->toWString();


    std::cout << "reset" << std::endl;
    field->resetField();
    std::wcout << field->toWString();

    std::cout << "Set unit" << std::endl;
    go = factory->createUnit(UnitClass::ALPHA);
//    objVector.push_back(go);
    field->setAt(*go, 5, 5);
    std::wcout << field->toWString();

    std::cout << "Set unit" << std::endl;
    go = factory->createUnit(UnitClass::BETA);
//    objVector.push_back(go);
    field->setAt(*go, 1, 1);
    std::wcout << field->toWString();

    std::cout << "Set unit" << std::endl;
    go = factory->createUnit(UnitClass::GAMMA);
//    objVector.push_back(go);
    field->setAt(*go, 6, 1);
    std::wcout << field->toWString();

    std::cout << "Set unit" << std::endl;
    go = factory->createUnit(UnitClass::ZETA);
//    objVector.push_back(go);
    field->setAt(*go, 3, 4);
    std::wcout << field->toWString();

    std::cout << "Swap unit" << std::endl;
    field->swap(5, 5, 1, 1);
    std::wcout << field->toWString();

*/

    //delete field;
    //field = new Field(fieldWidth, fieldHeight, fieldHeight * fieldWidth);

}

Game::~Game() {

}
