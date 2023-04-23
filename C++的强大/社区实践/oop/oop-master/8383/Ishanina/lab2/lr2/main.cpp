#include <iostream>
#include "Field/Field.h"

#include "AbstractFactory/ConcreteFactoryMagicHero.h"
#include "AbstractFactory/ConcreteFactoryStrongHero.h"
#include "Base/Base.h"
#include "NeutralObject/NeutralObject.h"
#include "NeutralObject/MedicalKit.h"
#include "NeutralObject/PowerPotion.h"
#include "NeutralObject/Stone.h"
#include "NeutralObject/Shild.h"

int main() {

    //system("chcp 65001");

    std::cout << "Hello, Player!" << std::endl;
    /*Gnome* gnome = new Gnome();
    NeutralObjectInterface* powerPotion = new PowerPotion();
    NeutralObjectInterface* medicalKit = new MedicalKit();
    (*medicalKit) + gnome->getHealthForUpdate();
    (*powerPotion) + gnome->getDamageForUpdate();

    std::cout << gnome->getHealth() << std::endl;
    std::cout << gnome->getDamage() << std::endl;*/



    int counter = 0;//счетчик для базы, чтобы каждая база имела свой номер




    auto *field = new Field(10, 10, 5);


    Unit** units = new Unit*[field->getControlMax()];//выделяем место для массива
    Base* base1 = new Base(field, units, ++counter, 4);

    field->appendElement(0,0,base1);
    base1->createUnit(1,4,5);
    base1->createUnit(4,5,4);
    base1->createUnit(5,7,9);
    base1->createUnit(3,1,9);
    //field->drawField();
    //std::cout<< "Health unit 'H':  " << field->getUnit(8,9)->getHealth() << std::endl;
    //field->move(8,9,9,9);
    //field->drawField();
    //std::cout<< "Health unit 'H':  " << field->getUnit(9,9)->getHealth() << std::endl;

    auto * medicalKit = new MedicalKit();
    auto * stone = new Stone();
    auto * powerPotion = new PowerPotion();
    auto * shild = new Shild();
    field ->addNeutralObject(7,8,stone);
    field->addNeutralObject(5,5,medicalKit);
    field->addNeutralObject(5,2, powerPotion);
    field->addNeutralObject(0,9, shild);
    field->drawField();
    //std::cout<< "Armor unit 'H':  " << field->getUnit(1,9)->getHealth() << std::endl;
    field->move(5,4,5,6);
    field->drawField();
    //std::cout<< "Armor unit 'H':  " << field->getUnit(0,9)->getHealth() << std::endl;
    /*field->move(5,5,3,3);
    std::cout<< field->getUnit(3,3)->getHealth() << std::endl;
    field->drawField();
    field->move(3,3,7,8);
    field->drawField();*/
    //field->move(3,3,0,0);//проверка встать на базу
    //field->move(3,3,5,6);//проверка прокси

    //field->drawField();
    //base1->createUnit(1,1,1);
    //base1->createUnit(4,5,1);
   /* std::cout<< field->getUnit(5,1)->getHealth() << std::endl;
    field->attack(1,1,5,1);
    field->drawField();
    std::cout<< field->getUnit(5,1)->getHealth() << std::endl;*/
    //base1->createUnit(5,8,8);
    //field->drawField();
    //field->move(5,1,5,6);
    //field->addNeutralObject(9,9, new Stone());
    //field->drawField();
    //std::cout << base1->getCountUnit() << std::endl;
    /*int a = base1->getCountUnit();
    ///очищаем память
    for (int i = a; i > -1; i--) {
        //std::cout << i <<std::endl;
        if(dynamic_cast<Archer *>(units[i]) != nullptr) {
            auto *archer = dynamic_cast<Archer *>(units[i]);
            delete archer;
        }
        else if(dynamic_cast<Magician *>(units[i]) != nullptr) {
            auto *magician = dynamic_cast<Magician *>(units[i]);
            delete magician;
        }
        else if(dynamic_cast<ElfOnUnicorn *>(units[i]) != nullptr) {
            auto *elfOnUnicorn = dynamic_cast<ElfOnUnicorn *>(units[i]);
            delete elfOnUnicorn;
        }
        else if(dynamic_cast<KnightOnHorse *>(units[i]) != nullptr) {
            auto *knightOnHorse = dynamic_cast<KnightOnHorse *>(units[i]);
            delete knightOnHorse;
        }
        else if(dynamic_cast<Gnome *>(units[i]) != nullptr) {
            auto *gnome = dynamic_cast<Gnome *>(units[i]);
            delete gnome;
        }
        else if(dynamic_cast<Knight *>(units[i]) != nullptr) {
            auto *knight = dynamic_cast<Knight *>(units[i]);
            delete knight;
        }
    }*/

    /*std::cout << "Проверка на перемещение юнита на карте" << std::endl;
    field1.move(2,2,4,3);
    field1.drawField();
    std::cout<<std::endl;
    field1.move(4,3,4,4);
    field1.drawField();*/

   // auto* field2 = new Field (12,12,5);
    //field2 = &field1;
    //std::cout << "Второе поле:" << std::endl;
    //field2->drawField();


    //auto* field2 = new Field(field1);


    //field1.deleteUnit(0,2);
    //field1.drawField();

    /*std::cout << "Проверка: создание поля произвольного объекта с контролируемым максимальным количеством объектов на поле"<<std::endl;
    auto *field = new Field(5,5,2);
    field->drawField();
    std::cout<<std::endl;
//Создание лучника
    auto *archer = new Archer();
    std::cout << "Добавление лучника на поле" << std::endl;
    field->appendUnit(1,1,archer);
    field->drawField();
    std::cout<<std::endl;


    //field->
//Создание мага
    auto* magician = new Magician();
    std::cout << "Добавление мага на поле" << std::endl;
    field->appendUnit(2,2,magician);
    field->drawField();
    std::cout<<std::endl;

    std::cout << "Проверка копирования поля с объектами на нём!" << std::endl;
    auto *field2 = new Field(*field);
    field2->drawField();

//Создание эльфа на единороге
    /*auto *elfOnUnicorn = new ElfOnUnicorn();
//Проверка на контроль макс количества объектов на поле!
    field->appendUnit(5,1,elfOnUnicorn);
    field->drawField();
    std::cout<<std::endl;
    std::cout << "Проверка на удаление юнита с поля" << std::endl;
    field->deleteUnit(1,1);
    field->drawField();
    std::cout<<std::endl;
    std::cout << "Проверка на перемещение юнита на карте" << std::endl;
    field->move(2,2,4,3);
    field->drawField();
    std::cout<<std::endl;
    field->move(4,3,4,4);
    field->drawField();*/

    return 0;
}
