#include "unit.h"
#include "field.h"
#include "cell.h"
#include "object.h"
#include "objectFabric.h"

int main(int argc, char *argv[])
{
    // создание фабрики
    objectFabric fabric;

    //создание поля
    Field field1(12, 12);
    //field1.print();

    //Добавление объектов на поле
    field1.addObject(fabric.createArcher(), 3, 2);
    field1.addObject(fabric.createCrossbowman(), 2, 2);
    field1.addObject(fabric.createLightRider(), 2, 3);
    field1.addObject(fabric.createHeavyRider(), 2, 4);
    field1.addObject(fabric.createKnight(), 4, 4);
    field1.addObject(fabric.createSpearman(), 12, 12);
    //field1.print();
    //Копирование поля
    Field field2 = field1;
    //field2.print();
    //перемещение
    field2.moveUnit(12,12, 11,11);
    field2.moveUnit(12,12, 11,12);
    field2.moveUnit(2,4, 3,6);
    //field2.print();
    field2.deleteObject(3, 2);
    //field1.print();
    //field2.print();
    //Конструкторы
    Field f(5,5);
    Field g = f;
    std::cout << g.H << ";" << g.W << std::endl;
    Cell r(6,6);
    Cell s(std::move(r));
    std::cout << s.x << ";" << s.y << std::endl;

    return 0;
}
