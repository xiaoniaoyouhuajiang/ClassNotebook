#ifndef OOP1_HANDLER_H
#define OOP1_HANDLER_H

#include <string>
#include <iostream>
#include "Base.h"
#include "Field.h"
#include "Command.h"

class BaseHandler{
    BaseHandler* next;
protected:
    Field* field;


    BaseHandler(Field* field): field(field){
        next = nullptr;
    }
public:
    BaseHandler(){
        next = nullptr;
    }


    void add(BaseHandler *n){
        if (next)
            next->add(n);
        else
            next = n;
    }

    virtual void handle(std::string commandStr, int player)
    {
        next->handle(commandStr, player);
    }
};

class SetBaseHandler: public BaseHandler{
    int x, y, maxCount, health;
    Adapter* adapter;
public:
    SetBaseHandler(Field* field, Adapter* adapter): BaseHandler(field), adapter(adapter){

    }
    void handle (std::string commandStr, int player) override {
        if (commandStr == "setBase"){
            std::cout << "Set x of base:" << std::endl;
            std::cin >> x;
            std::cout << "Set y of base: "<< std::endl;
            std::cin >> y;
            std::cout << "Set maximum count unit of base: "<< std::endl;
            std::cin >> maxCount;
            std::cout << "Set  health of base: "<< std::endl;
            std::cin >> health;
            std::cout << std::endl;
            BaseCommand* setBase = new SetBaseCommand(field, x, y, maxCount, health, adapter);
            setBase->execute();
        }
        else{
            BaseHandler::handle(commandStr, player);
        }

    }
};

class SwitchLogHandler: public BaseHandler{
    Adapter* adapter;
    std::string command;
public:
    SwitchLogHandler(Adapter* adapter): adapter(adapter){

    }
    void handle (std::string commandStr, int player) override {
        if (commandStr == "switchLog"){
            std::cin >> command;
            if (command == "off"){
                adapter->writeAble = false;
                adapter->switchLog("off");
            }
            else if(command == "on") {
                adapter->writeAble = true;
                adapter->switchLog("on");
            }
            else if(command == "file"){
                adapter->fileWriteAble = true;
                adapter->switchLog("write to file");
            }
            else if(command == "console"){
                adapter->fileWriteAble = false;
                adapter->switchLog("write to console");
            }
            else{
                std::cout << "No exist this command" << std::endl;
            }
        }
        else{
            BaseHandler::handle(commandStr, player);
        }

    }
};


class SetUnitHandler: public BaseHandler{
    Mediator* mediator;
    Adapter* adapter;
    int number;
public:
    SetUnitHandler(Field* field, Mediator* mediator, Adapter* adapter): BaseHandler(field), mediator(mediator), adapter(adapter){

    }
    void handle (std::string commandStr, int number) override {
        if (commandStr == "setUnit"){
            if (number <= 0 || number > 3){
                std::cout << "Incorrect number base"<<std::endl;
                return;
            }

            BaseCommand* setUnit = new CreateUnitCommand(field, mediator, adapter, number);
            setUnit->execute();

        }
        else{
            BaseHandler::handle(commandStr, number);
        }

    }
};


class SaveHandler: public BaseHandler{
public:
    SaveHandler(Field* field): BaseHandler(field){

    }
    void handle (std::string commandStr, int player) override {
        if (commandStr == "save"){
            SnapshotField* snap = field->createSnap();
            snap->save();

        }
        else{
            BaseHandler::handle(commandStr, player);
        }

    }
};

class LoadHandler: public BaseHandler{
    Mediator* mediator;
public:
    LoadHandler(Field* field, Mediator* mediator): BaseHandler(field), mediator(mediator){

    }
    void handle (std::string commandStr, int player) override {
        if (commandStr == "load"){
            SnapshotField* snap = field->createSnap();
            snap->load(mediator);
        }
        else{
            BaseHandler::handle(commandStr, player);
        }

    }
};

class AttackUnitHandler: public BaseHandler{
public:
    AttackUnitHandler(Field* field): BaseHandler(field){

    }
    void handle (std::string commandStr, int number) override {
        if (commandStr == "attackUnit"){
            if (number <= 0 || number > 3){
                std::cout << "Incorrect number base"<<std::endl;
                return;
            }
            BaseCommand* attackUnit = new AttackUnitCommand(field, number);
            attackUnit->execute();

        }
        else{
            BaseHandler::handle(commandStr, number);
        }

    }
};

class StatusBaseHandler: public BaseHandler{
public:
    StatusBaseHandler(Field* field): BaseHandler(field){

    }
    void handle (std::string commandStr, int number) override {
        if (commandStr == "statusBase"){
            if (number <= 0 || number > 3){
                std::cout << "Incorrect number base"<<std::endl;
                return;
            }
            StatusBaseCommand* statusBase = new StatusBaseCommand(field, number);
            statusBase->execute();

        }
        else{
            BaseHandler::handle(commandStr, number);
        }

    }
};

class MoveUnitHandler: public BaseHandler{
public:
    MoveUnitHandler(Field* field): BaseHandler(field){

    }
    void handle (std::string commandStr, int number) override {
        if (commandStr == "moveUnit"){
            if (number <= 0 || number > 3){
                std::cout << "Incorrect number base"<<std::endl;
                return;
            }
            MoveUnitCommand* moveUnit = new MoveUnitCommand(field, number);
            moveUnit->execute();

        }
        else{
            BaseHandler::handle(commandStr, number);
        }

    }
};

class NoCommandHandler: public BaseHandler{
public:
    void handle (std::string commandStr, int player) override {
        std::cout << "Not this command!" << std::endl;
    }
};

#endif //OOP1_HANDLER_H
