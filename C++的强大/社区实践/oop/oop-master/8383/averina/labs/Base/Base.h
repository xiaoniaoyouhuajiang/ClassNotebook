#ifndef OOP_BASE_H
#define OOP_BASE_H

#include <map>
#include "../Unit/Object/ObjectFactory.h"
#include "UnitComposite.h"

/* Base -- класс базы.
 * --------------- ФУНКЦИИ --------------------
 * createUnit -- создать юнита на базе
 * getInformation -- информация о юнитах на базе,
 * наблюдение за юнитами на поле.
 * getUnit -- "забрать" юнита с базы на поле.
 * update -- обновить информацию для субъекта наблюдения.
 * ---------------------------------------------
 * unitsOnBase -- юниты на базе.
 * unitsOnField -- юниты, выпущенные с базы.
 * unitFactory -- абстрактная фабрика объектов для
 * создания юнитов
 * unitLimit -- лимит юнитов для хранения на базе.
 * unitCount, unitDead -- счетчики для юнитов на
 * базе и поле соответственно.
 */


class Field;

class Base : public Object, public IObserver
{
    friend class Snapshot;
    friend class Field;
public:
    Base(Field* field, int x, int y, int unitLimit);

    void createUnit(char id);
    void getInformation() override ;
    IUnit* getUnit(char id);
    void update(Subject* subject) override ;
    int y, x;
    int unitLimit;    //  лимит юнитов в базе
    int gold;        //   голды - очки на создание юнитов на базе
                    //    изначально 3 голды - возможность создать 3 юнита
                   //    увеличиваются при пропуске хода

    UnitComposite unitsOnField;
    std::map<char, int> unitsOnBase;
    int unitDead;      // счетчик умерших юнитов
    int unitCount;    //  счетчик юнитов
private:
    ObjectFactory unitFactory;
    Field* field;
};




#endif //OOP_BASE_H
