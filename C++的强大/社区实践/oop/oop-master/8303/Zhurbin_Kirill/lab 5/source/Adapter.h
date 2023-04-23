#ifndef OOP1_ADAPTER_H
#define OOP1_ADAPTER_H

#include <string>
#include "Logger.h"

class Base;
class Unit;
class Field;
class Adapter : public Logger{
public:
    bool writeAble;
    bool fileWriteAble;

    Adapter(bool writeAble = true, bool fileWriteAble = false);

    void unitDeath(char name);

    void createUnit(Unit* unit);

    void attackBase(int numberBase);

    void unitAttacked(char name);

    void moveUnit(char name, int x, int y);

    void unitAttackBase(char name, int numberBase);

    void unitAttackUnit(char name1, char name2);

    void switchLog(std::string mod);

    void createBase(Base *base);

    void createField(Field *field);

    void incorrectFile();

    void gameSaved();

    void gameLoaded();
};

#endif //OOP1_ADAPTER_H
