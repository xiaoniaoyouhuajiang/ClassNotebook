//
// Created by alexg on 03.06.2020.
//

#ifndef LABS_RULES_H
#define LABS_RULES_H

#include "../Field.h"

#include "State.h"

class RuleBase{
protected:
    Field* field;
    State* state1;
    State* state2;
    State* currentState;
public:
    RuleBase(){
        state1 = new State1();
        state2 = new State2();
        currentState = state1;
    }

    void changeState(){
        if (currentState == state1) {
            currentState = state2;
            std::cout << "Activate player 0" << std::endl;
        }
        else{
            currentState = state1;
            std::cout << "Activate player 1" << std::endl;
        }
    }

    void printState() {
        if (currentState == state1) {
            std::cout << "player 0" << std::endl;
        }
        else {
            std::cout << "player 1" << std::endl;
        }
    }
    virtual Field* createField(Adapter* adapter) = 0;
    virtual void handle(const std::string command, chainOfResponsibility *basecomm) = 0;
};

class Rule1: public RuleBase{

public:
    Field* createField(Adapter* adapter) override {
        field = new Field(8, 8, 20, adapter);
        field->createBase(0, 3,4, 10, 100);
        field->createBase(1, 5,2, 20, 50);
        field->getBase(0)->createUnit('S');
        field->getBase(1)->createUnit('M');
        return field;
    }
    int isLose(Field* field) {
        if(!field)
            return -1;
        // проигрыш, если на поле нет юнитов
        Base* base0 = field->getBase(0);
        Base* base1 = field->getBase(1);
        if(!base0 || !base1)
            return -1;
        int n1 = base0->countAllUnits();
        int n2 = base1->countAllUnits();
        if(n1==0 && n2==0)
            return 2; // draw
        if(n1==0)
            return 0;
        if(n2==0)
            return 1;
        return -1;
    }
    void handle(const std::string command, chainOfResponsibility *basecomm) override {
        currentState->handle(command, basecomm);
        if (command == "moveUnit" || command == "setUnit")
            changeState();
    }
};

class Rule2: public RuleBase{
public:
    Field* createField(Adapter* adapter) override {
        field = new Field(11, 11, 20, adapter);
        field->createBase(0, 0,0, 10, 100);
        field->createBase(1, 9,9, 20, 50);
        field->getBase(0)->createUnit('R');
        field->getBase(1)->createUnit('R');
        return field;
    }

    int isLose(Field* field) {
        if(!field)
            return -1;

        Base* base0 = field->getBase(0);
        Base* base1 = field->getBase(1);
        if(!base0 || !base1)
            return -1;

        // проигрыш если на базе никого нет!
        int n1 = base0->countUnitsAtBase();
        int n2 = base1->countUnitsAtBase();
        if(n1==0 && n2==0)
            return 2; // draw
        if(n1==0)
            return 0;
        if(n2==0)
            return 1;
        return -1;
    }
    void handle(const std::string command, chainOfResponsibility *basecomm) override {
        currentState->handle(command, basecomm);
        if (command == "moveUnit" || command == "setUnit")
            changeState();
    }
};

#endif //LABS_RULES_H
