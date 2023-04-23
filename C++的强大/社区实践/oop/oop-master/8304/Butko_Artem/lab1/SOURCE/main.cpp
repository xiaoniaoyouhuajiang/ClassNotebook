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


int main()
{
    exec();
    return 0;
}
