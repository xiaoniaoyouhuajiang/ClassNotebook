#ifndef COMMAND_H
#define COMMAND_H

#include <string.h>
#include "gamefield.h"
#include "mediator.h"
#include "loggerproxy.h"

using namespace std;

class Command{

public:
    virtual ~Command() {}
    virtual void execute() = 0;
    Command(GameField* field) : field(field) {}
    Command(GameField* field, Mediator* mediator) : field(field), mediator(mediator) {}

protected:
    GameField* field;
    Mediator* mediator;
};

class CreateBaseCommand : public Command{

    int maxUnitsCount, health, x, y;

public:
    CreateBaseCommand(GameField* field, int maxUnitsCount, int health, int x, int y) : Command(field), maxUnitsCount(maxUnitsCount),
        health(health), x(x), y(y){}
    void execute() override{
        field->setBase(maxUnitsCount, health, x, y);
    }
};


class CreateUnitCommand : public Command{

    int baseNumb, n;

public:
    CreateUnitCommand(GameField* field, Mediator* mediator, int n, int baseNumb) : Command(field, mediator), n(n), baseNumb(baseNumb){}
    void execute() override{
        for (int i = 0; i < n; i++){
            cout << "Enter unit's type: ";
            string unitName;
            getline(cin, unitName);
            if (baseNumb == 1){
                if (field->createUnit(unitName, field->base1, mediator) == 0)
                    return;
            }
            else if (baseNumb == 2){
                if (field->createUnit(unitName, field->base2, mediator) == 0)
                    return;
            }
            else{
                if(field->createUnit(unitName, field->base3, mediator) == 0)
                    return;
            }
        }
    }
};

class MoveUnitCommand : public Command{

    Base* base;
    Unit* currUnit;
    string str;

public:
    MoveUnitCommand(GameField* field, string str, Base* base, Unit* currUnit) : Command(field), str(str), base(base), currUnit(currUnit){}
    void execute() override{
        if(str == "w")
            field->moveUnitUp(currUnit, base);
        else if(str == "s")
            field->moveUnitDown(currUnit, base);
        else if(str == "a")
            field->moveUnitLeft(currUnit, base);
        else if(str == "d")
            field->moveUnitRight(currUnit, base);
    }
};

class BaseStatusCommand : public Command{

    int baseNumb;
    Base* currBase;

public:
    BaseStatusCommand(GameField* field, Base* currBase, int baseNumb) : Command(field), currBase(currBase), baseNumb(baseNumb){}
    void execute() override{
        cout << "Base " << baseNumb << " (" << currBase->x << ";" << currBase->y << ")\n";
        cout << "*Health " << currBase->health << endl;
        cout << "*Current count of units on field / Max count on base: " << currBase->unitCount << "/" << currBase->maxCount << endl;
        field->printBase(currBase);
    }
};

class AttackCommand : public Command{

    string str;
    Unit* currUnit;
    Point* currPoint;

public:
    AttackCommand(GameField* field, Mediator* mediator, string str, Unit* currUnit, Point* currPoint) : Command(field, mediator),
        str(str), currUnit(currUnit), currPoint(currPoint){}
    void execute() override{
        if(str == "w")
            currUnit->mediator->attack(currUnit, currPoint->x, (currUnit->getArmyType() == "Archer") ? currPoint->y - 2 : currPoint->y - 1);
        else if(str == "s")
            currUnit->mediator->attack(currUnit, currPoint->x, (currUnit->getArmyType() == "Archer") ? currPoint->y + 2 : currPoint->y + 1);
        else if(str == "a")
            currUnit->mediator->attack(currUnit, (currUnit->getArmyType() == "Archer") ? currPoint->x - 2 : currPoint->x - 1, currPoint->y);
        else if(str == "d")
            currUnit->mediator->attack(currUnit, (currUnit->getArmyType() == "Archer") ? currPoint->x + 2 :currPoint->x + 1, currPoint->y);
    }
};

class LogOnOffCommand : public Command{

    string options;

public:
    LogOnOffCommand(GameField* field, string options) : Command(field), options(options){}
    void execute() override{
        if (options == "off"){
            LoggerProxy::offLog();
            cout << "logging off\n";
        }
        else if (options == "toFile"){
            LoggerProxy::logToFile();
            cout << "logging to file\n";
        }
        else {
            LoggerProxy::logToConsole();
            cout << "logging to console\n";
        }
    }
};

class SaveGameCommand : public Command{

public:
    SaveGameCommand(GameField* field) : Command(field){}
    void execute() override{
        FieldSnapshot* fieldSnap = field->getSnapshot();
        fieldSnap->save();
    }
};

class LoadGameCommand : public Command{

public:
    LoadGameCommand(GameField* field, Mediator* mediator) : Command(field, mediator){}
    void execute() override{
        FieldSnapshot* fieldSnap = field->getSnapshot();
        fieldSnap->load(mediator);
    }
};

#endif // COMMAND_H
