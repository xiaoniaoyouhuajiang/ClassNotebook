#ifndef OOP1_RULES_H
#define OOP1_RULES_H

#include "Field.h"
#include "State.h"

class RuleBase{
protected:
    Field* field;
    State* state1;
    State* state2;
    State* state3;
    State* currentState;
public:

    RuleBase(){
        state1 = new State1();
        state2 = new State2();
        state3 = new State3();
        currentState = state1;
    }

    void changeState(int countPlayer){
        if (currentState == state1) {
            currentState = state2;
            std::cout << "Step 2 player" << std::endl;
        }
        else if (currentState == state2 && countPlayer == 3){
            currentState = state3;
            std::cout << "Step 3 player" << std::endl;
        }
        else{
            currentState = state1;
            std::cout << "Step 1 player" << std::endl;
        }
    }

    virtual Field* createField(Adapter* adapter) = 0;
    virtual void handle(const std::string command, int countPlayers, BaseHandler* handler) = 0;

};

class Rule1: public RuleBase{

public:
    Field* createField(Adapter* adapter) override {
        field = new Field(8, 8, 20, adapter);
        field->addLandscape();

        field->addNeutral(1, 1, 'z');
        field->addNeutral(2, 2, 'p');
        field->addNeutral(3, 3, 's');
        field->addNeutral(4, 4, 'a');

        return field;
    }

    int isLose(Field* field, int countPlayer) {
        if (field->base1->isDestroyed())
            return 1;
        else if (field->base2->isDestroyed())
            return 2;
        else if (countPlayer == 3 && field->base3->isDestroyed())
            return 3;
        else
            return 0;
    }

    void handle(const std::string command, int countPlayers, BaseHandler* handler) override {
        currentState->handle(command, handler);
        if (command == "attackUnit" || command == "moveUnit" || command == "setUnit")
            changeState(countPlayers);
    }


};

class Rule2: public RuleBase{
public:
    Field* createField(Adapter* adapter) override {
        field = new Field(10, 10, 20, adapter);
        field->addLandscape();

        field->addNeutral(1, 7, 'z');
        field->addNeutral(5, 2, 'p');
        field->addNeutral(3, 2, 's');
        field->addNeutral(2, 4, 'a');

        return field;
    }

    int isLose(int countMove, Field* field) {
        if (field->base1->isDestroyed())
            return 1;
        else if ((countMove > 50 && !field->base1->isDestroyed()) || field->base2->isDestroyed())
            return 2;
        else
            return 0;
    }


    void handle(const std::string command, int countPlayers, BaseHandler* handler) override {
        currentState->handle(command, handler);
        if (command == "attackUnit" || command == "setUnit")
            changeState(countPlayers);
    }
};

#endif //OOP1_RULES_H
