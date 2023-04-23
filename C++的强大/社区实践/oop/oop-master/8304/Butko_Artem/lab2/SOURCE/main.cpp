#include <iostream>
#include "Game/GameField/Field/Field.h"
#include "Game/Factories/ObjectFactory/ObjectFactory.h"

/* пример работы созданных структур */
void exec()
{
    /* Создание игрового поля */
    Field field(5, 5);
    /* Создание фабрики объектов */
    ObjectFactory factory;
    /* Добавление рыцаря на поле */
    field.addObject(factory.createKnight(), 2, 2);
    field.show();
    std::cout << std::endl;
    /* Попытка поставить на рыцаря мага */
    field.addObject(factory.createMage(), 2, 2);
    field.show();
    std::cout << std::endl;
    /* Перемещение юнита */
    field.moveObject(2, 2, 1, 1);
    field.show();
    std::cout << std::endl;
    /* Копирование поля и добавление на него нового объекта */
    Field newField(field);
    newField.addObject(factory.createWizard(), 2, 1);
    newField.show();
    std::cout << std::endl;
    /* Удаление объекта с нового поля */
    newField.deleteObject(1, 1);
    newField.show();
    std::cout << std::endl;
    /* Старое поле */
    field.show();
    std::cout << std::endl;
}

void exec2()
{
    /* Создание поля */
    Field field(10, 10);
    field.show();
    /* Попытка создания базы */
    field.createBase(9, 9, 10);
    field.show();
    /* Создание базы */
    field.createBase(5, 5, 10);
    field.show();
    /* Создание 11 юнитов на базе при лимите в 10 юнитов */
    field.base->createUnit('A');
    field.base->createUnit('K');
    field.base->createUnit('C');
    field.base->createUnit('W');
    field.base->createUnit('M');
    field.base->createUnit('C');
    field.base->createUnit('W');
    field.base->createUnit('S');
    field.base->createUnit('S');
    field.base->createUnit('A');
    field.base->createUnit('K');
    /* Вывод информации от базы */
    field.base->getInformation();
    /* Переставим юнитов на поле */
    field.addObject(field.base->getUnit('A'), 1, 1);
    field.addObject(field.base->getUnit('S'), 1, 2);
    field.addObject(field.base->getUnit('M'), 1, 3);
    field.show();
    /* Снова выведем информацию о юнитах */
    field.base->getInformation();
    /* Убьем юниты и выведем информацию */
    field.immediateDeath(1, 1);
    field.immediateDeath(1, 2);
    field.immediateDeath(1, 3);
    field.show();
    field.base->getInformation();
    /* Выставим других юнитов на поле */
    field.addObject(field.base->getUnit('K'), 3, 3);
    field.addObject(field.base->getUnit('S'), 7, 7);
    field.addObject(field.base->getUnit('W'), 2, 9);
    /* Передвинем их */
    field.moveObject(3,3,1,1);
    field.moveObject(7, 7, 8, 8);
    field.moveObject(2, 9, 2, 8);
    field.show();
    /* Атакуем одним юнитом другого */
    std::cout << "ATTACK" << std::endl;
    field.makeDamage(8, 8, 2, 8);
    field.makeDamage(8, 8, 2, 8);
    field.makeDamage(8, 8, 2, 8);
    field.makeDamage(8, 8, 2, 8);
    field.show();
    field.base->getInformation();
}

int main()
{
    //exec();
    exec2();
    return 0;
}
