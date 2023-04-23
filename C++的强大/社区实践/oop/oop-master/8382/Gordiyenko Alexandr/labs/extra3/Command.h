//
// Created by alexg on 03.06.2020.
//

#ifndef LABS_COMMAND_H
#define LABS_COMMAND_H

#include "../Field.h"
#include "../Base.h"
#include "../Exceptions.h"
#include <string>

class Command{
public:
    virtual void execute() = 0;
protected:
    Adapter *adapter;
    Command(Field* field): field(field) {}
    Field* field;
    std::string param;
};

class createBaseCommand : public Command{
private:
    std::string idS, xS, yS, maxUnitS, healthS;
    int id, x, y, maxUnit, health;
public:
    createBaseCommand(Field* field) : Command(field) {
    }

    void execute() override{
        std::cout << "Select id of base 0/1:" << std::endl;
        std::cin >> idS;
        std::cout << "Set x of base:" << std::endl;
        std::cin >> xS;
        std::cout << "Set y of base: "<< std::endl;
        std::cin >> yS;
        std::cout << "Set maximum count unit of base: "<< std::endl;
        std::cin >> maxUnitS;
        std::cout << "Set  health of base: "<< std::endl;
        std::cin >> healthS;
        std::cout << std::endl;

        field->createBase(id, x, y, maxUnit, health);

        try {
            id = std::stoi(idS);
            x = std::stoi(xS);
            y = std::stoi(yS);
            maxUnit = std::stoi(maxUnitS);
            health = std::stoi(healthS);
        } catch (std::exception) {
            throw InputException("int");
        }

        if (x < 0 || x > field->x - 1)
            throw LogicException("base coordinates", x);
        if (y < 0 || y > field->y - 1)
            throw LogicException("base coordinates", y);
        if (maxUnit < 0 || maxUnit > field->maxUnit)
            throw LogicException("max count unit of base", maxUnit);
        if (health <= 0)
            throw LogicException("health of base", health);
        field->createBase(id, x, y, maxUnit, health);
    }
};

class switchLogCommand : public Command {
private:
    std::string command;
public:
    switchLogCommand(Field* field) :Command (field){ }
    void execute() override{
        std::cout<<"choose command for log switch: \nfileOff, fileOn, consoleOff, consoleOn";
        std::cin >> command;
        if (command == "fileOff"){
            field->adapter->switchLog("fileOff");
        }
        else if(command == "fileOn") {
            field->adapter->switchLog("fileOn");
        }
        else if(command == "consoleOff"){
            field->adapter->switchLog("consoleOff");
        }
        else if(command == "consoleOn"){
            field->adapter->switchLog("consoleOn");
        }
        else{
            std::cout << "No exist this command for log" << std::endl;
            std::cout << "use: fileOff, fileOn, consoleOff, consoleOn" << std::endl;
        }
    }
};

class baseInfoCommand : public Command {
public:
    baseInfoCommand(Field* field) : Command(field) {
    }
    void execute() {
        std::cout << "Input base id: ";
        int id;
        std::cin >> id;
        Base *base = field->getBase(id);
        if(base)
            base->printInfo();
        else {
            std::cout << "There is not any base!" << std::endl;
        }
    }
};

class createUnitCommand : public Command {
public:
    createUnitCommand(Field* field, std::string param) : Command(field) {
        this->param = param;
    }
    createUnitCommand(Field* field) : Command(field) {

    }
    void execute() {
        std::cout << "CreateUnitCommand" << std::endl;
        int id;
        if(param=="0")
            id = 0;
        else if(param == "1")
            id = 1;
        else {
            std::cout << "Input base id: ";
            std::cin >> id;
        }

        Base *base = field->getBase(id);
        if(base) {
            std::cout << "which type of unit you want to create? ";
            char c;
            std::cin >> c;
            base->createUnit(c);
        }
        else {
            std::cout << "Can't create unit without base!" << std::endl;
        }
    }
};

class moveUnitCommand : public Command {
public:
    moveUnitCommand(Field* field, std::string param) : Command(field) {
        this->param = param;
    }
    moveUnitCommand(Field* field) : Command(field) {
    }
    void execute() {
        std::cout << "MoveUnitCommand" << std::endl;

        int id;
        if(param=="0")
            id = 0;
        else if(param == "1")
            id = 1;
        else {
            std::cout << "Input base id: ";
            std::cin >> id;
        }

        Base *base = field->getBase(id);
        if(base!=nullptr && base->countAllUnits()>0) {
            base->printUnits();

            std::cout << "input # of unit to move: ";
            int id;
            std::cin >> id;

            std::cout << "input direction to move (wasd): ";
            char d;
            std::cin>>d;

            Unit *unit = base->getUnitById(id);
            int x = unit->getx();
            int y = unit->gety();

            switch(d) {
                case 'w': field->moveUnit(unit, x, y-1); break;
                case 'a': field->moveUnit(unit, x-1, y); break;
                case 's': field->moveUnit(unit, x, y+1); break;
                case 'd': field->moveUnit(unit, x+1, y); break;
            }
        }
        else {
            std::cout << "There is not any unit!" << std::endl;
        }
    }
};

class SaveCommand : public Command {
public:
    SaveCommand(Field *field): Command(field){}

    void execute() {
        SnapshotBackup *snap = field->createSnap("save");
        snap->saveGame();
    }
};

class LoadCommand : public Command {
public:
    LoadCommand(Field *field) : Command(field){}

    void execute() {
        SnapshotBackup *snap = field->createSnap("load");
        snap->loadGame();
    }
};

class uknownCommand : public Command {
public:
    uknownCommand() : Command(nullptr){
    }
    void execute() {
        std::cout << "Uknown command!!!" << std::endl;
    }
};

#endif //LABS_COMMAND_H
