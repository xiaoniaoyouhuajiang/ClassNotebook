#ifndef OOP_UNITCOMPOSITE_H
#define OOP_UNITCOMPOSITE_H

#include <iostream>
#include <vector>
#include "../Unit/Object/Object.h"


/* UnitComposit -- класс-композит (контейнер) для юнитов.
 * ------------------------------------------------------
 * addUnit -- добавить юнита в контейнер.
 * deleteUnit -- удалить юнита из контейнера.
 * getInformation -- информация о юнитах, находящихся
 * в контейнере.
 */

class UnitComposite : public Object
{
public:
    UnitComposite();
    void addUnit(Object* unit);
    void deleteUnit(Object* unit);
    void getInformation();
    std::vector<Object*> composite;
};



#endif //OOP_UNITCOMPOSITE_H
