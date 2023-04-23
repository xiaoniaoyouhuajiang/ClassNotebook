#include <iostream>
#include "Field/Field.h"

#include "AbstractFactory/ConcreteFactoryMagicHero.h"
#include "AbstractFactory/ConcreteFactoryStrongHero.h"

int main() {
    //system("chcp 65001");

    std::cout << "Hello, Player!" << std::endl;

    // создание фабрик
    auto *f1 = new ConcreteFactoryMagicHero();
    auto *f2 = new ConcreteFactoryStrongHero();

    //создание поля 1
    Field field1(12, 12, 5);
    //создание юнитов
    Unit* magician = f1->CreateArtillerist();
    Unit* archer = f2->CreateArtillerist();
    Unit* elf_on_unicorn = f1->CreateCavalryman();
    Unit* knight_on_horse = f2->CreateCavalryman();
    Unit* gnome = f1->CreateInfantryman();
    Unit* knight = f2->CreateInfantryman();

    //Добавление объектов на поле
    field1.appendUnit(2, 2, magician);
    field1.appendUnit(6, 8, archer);
    field1.appendUnit(11, 11, knight);
    field1.appendUnit(0, 2, elf_on_unicorn);
    field1.appendUnit(5, 0, knight_on_horse);
    field1.appendUnit(6, 0, gnome); //для демонстрационного примера добавляется шестой юнит,
                                                // но при выводе будет видно, что он не добавится, т к
                                                // уже добавлено максимальное количество юнитов на поле

    /*field1.drawField();
    std::cout << "Проверка на перемещение юнита на карте" << std::endl;
    field1.move(2,2,4,3);
    field1.drawField();
    std::cout<<std::endl;
    field1.move(4,3,4,4);*/
    field1.drawField();

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
