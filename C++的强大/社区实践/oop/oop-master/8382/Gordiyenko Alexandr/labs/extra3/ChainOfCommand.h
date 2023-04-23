#ifndef CHAINOFCOMMAND_H
#define CHAINOFCOMMAND_H
#include "../Field.h"
#include "Command.h"
#include "../Base.h"

class chainOfResponsibility{
    chainOfResponsibility *next;
protected:
    Field *field;

    chainOfResponsibility(Field *field) : field(field){
        next = nullptr;
    }

public:
    chainOfResponsibility(){
        next = nullptr;
    }


    void setNext(chainOfResponsibility *n){
        next = n;
    }
    void add(chainOfResponsibility *n){
        if (next)
            next->add(n);
        else
            next = n;
    }

    virtual void chainOR(std::string commandStr)
    {
        next->chainOR(commandStr);
    }

};


class SwitchLogCor: public chainOfResponsibility{
    std::string command;
public:
    SwitchLogCor(Field *field) : chainOfResponsibility(field) {

    }
    void chainOR (std::string strCommand) override {
        if (strCommand == "switchLog"){
            Command* cmd = new switchLogCommand(field);
            cmd->execute();
        }
        else {
            chainOfResponsibility::chainOR(strCommand);
        }
    }
};

class createBaseCor: public chainOfResponsibility{
public:
    createBaseCor(Field *field): chainOfResponsibility(field){

    }
    void chainOR (std::string strCommand) override {
        if (strCommand == "setBase"){
            Command* cmd = new createBaseCommand(field);
            cmd->execute();
        }
        else{
            chainOfResponsibility::chainOR(strCommand);
        }
    }
};

class baseInfoCor: public chainOfResponsibility {
public:
    baseInfoCor(Field *field): chainOfResponsibility(field){

    }
    void chainOR (std::string strCommand) override {
        if (strCommand == "baseInfo"){
            Command* cmd = new baseInfoCommand(field);
            cmd->execute();
        }
        else{
            chainOfResponsibility::chainOR(strCommand);
        }
    }

};

class createUnitCor: public chainOfResponsibility {
public:
    createUnitCor(Field *field): chainOfResponsibility(field){

    }
    void chainOR (std::string strCommand) override {
        if (strCommand == "setUnit"){
            Command* cmd = new createUnitCommand(field);
            cmd->execute();
        }
        else{
            chainOfResponsibility::chainOR(strCommand);
        }
    }

};

class moveUnitCor: public chainOfResponsibility {
public:
    moveUnitCor(Field *field): chainOfResponsibility(field){

    }
    void chainOR (std::string strCommand) override {
        if (strCommand == "moveUnit"){
            Command* cmd = new moveUnitCommand(field);
            cmd->execute();
        }
        else{
            chainOfResponsibility::chainOR(strCommand);
        }
    }
};

class  saveCor: public chainOfResponsibility {
public:
    saveCor(Field *field) : chainOfResponsibility(field){
    }

    void chainOR(std::string strCommand) override{
        if(strCommand == "save"){
            Command *cmd = new SaveCommand(field);
            cmd->execute();
        }
        else{
            chainOfResponsibility::chainOR(strCommand);
        }

    }
};

class loadCor : public chainOfResponsibility {
public:
    loadCor(Field *field) : chainOfResponsibility(field){
    }

    void chainOR(std::string strCommand) override{
        if(strCommand == "load"){
            Command *cmd = new LoadCommand(field);
            cmd->execute();
        }
        else{
            chainOfResponsibility::chainOR(strCommand);
        }

    }
};


class uknownCmdCor: public chainOfResponsibility {
public:
    uknownCmdCor(): chainOfResponsibility(nullptr){}

    void chainOR (std::string strCommand) override {
        Command* cmd = new uknownCommand;
        cmd->execute();
    }
    // Здесь цепочка обязанностей обрывается
};

#endif // CHAINOFCOMMAND_H
