#include <iostream>
//#include "gamefield.h"
//#include "iterator.h"
//#include "base.h"
//#include "NeutralObject/poison.h"
//#include "NeutralObject/armor.h"
//#include "NeutralObject/weapon.h"
//#include "NeutralObject/medicine.h"
//#include "basehandler.h"
//#include "mediator.h"
#include "facade.h"

using namespace std;

int main()
{
    Facade* facade = new Facade;

    facade->prepareGame();

    /*GameField field(7, 7, 7);
    Mediator* mediator = new Mediator(&field);
    BaseHandler* baseHandler = new BaseHandler();
    CreateBaseHandler* createBaseHandler = new CreateBaseHandler(&field);
    CreateUnitHandler* createUnitHandler = new CreateUnitHandler(&field, mediator);
    MoveUnitHandler* moveUnitHandler = new MoveUnitHandler(&field);
    BaseStatusHandler* baseStatusHandler = new BaseStatusHandler(&field);
    AttackHandler* attackHandler = new AttackHandler(&field, mediator);
    WrongCommandHandler* wrongCommandHandler = new WrongCommandHandler();
    baseHandler->add(createBaseHandler);
    baseHandler->add(createUnitHandler);
    baseHandler->add(moveUnitHandler);
    baseHandler->add(baseStatusHandler);
    baseHandler->add(attackHandler);
    baseHandler->add(wrongCommandHandler);*/

    /*while(true){
        string commandStr;
        cout << "Enter command:" << endl;
        getline(cin, commandStr);
        baseHandler->handle(commandStr);
        field.printAll();
    }*/
    /*Base* base = field.setBase(3, 100, 3, 4);
    Base* base2 = field.setBase(3, 100, 6, 5);
    for (int i = 0; i < 100; i++)                   //
        field.createUnit("Flatbow", base, mediator);
    base->printAll();

    std::cout << "--------------------\n";          // Демонстрация 1 - создание юнитов, их смерть, реакция базы


    for (int i = 0; i < 100; i++){
        field.createUnit("Spearman", base2, mediator);              //
        field.createUnit("Hussar", base2, mediator);
    }

    base2->printAll();

    field.printAll();                             // Демонстрация 2 - размещение юнитов и баз на поле с учётом ландшафта

    /*Iterator iter(&field);
    while (iter.hasNext()){
        cout << (*iter)->armyType << endl;
        iter++;
    }*/

    //DrinkPoison* drinkPoison = new DrinkPoison(new ArcherPoison);
    //GetArmor* getArmor = new GetArmor(new ArcherArmor);
    //GetWeapon* getWeapon = new GetWeapon(new ArcherWeapon);
    //GetMedicine* getMedicine = new GetMedicine(new ArcherMedicine);

    /*Iterator iter(&field);
    while (iter.hasNext()){
        //drinkPoison->drinkPoison(*iter);
        //getArmor->getArmor(*iter);                // Демонстрация 3 - взаимодействие юнитов с нейтральными объектами (яд для лучника)
        //getWeapon->getWeapon(*iter);
        *drinkPoison == *iter;
        iter++;
    }
    field.printAll();
    //base->printAll();
    //field.printAll();*/
    return 0;
}
