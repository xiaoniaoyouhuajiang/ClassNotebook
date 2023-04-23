//
// Created by Artem Butko on 15/05/2020.
//

#ifndef OOP_NEW_UNITCOMPOSITE_H
#define OOP_NEW_UNITCOMPOSITE_H

#include <iostream>
#include "../../Object.h"

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
private:
    std::vector<Object*> composite;
};


#endif //OOP_NEW_UNITCOMPOSITE_H
