#ifndef RULE_H
#define RULE_H

#include "gamefield.h"
#include "state.h"

class Rule{

protected:
    State* currState;
    Player1StepState* state1;
    Player2StepState* state2;
    Player3StepState* state3;

public:
    Rule(): state1(new Player1StepState), state2(new Player2StepState), state3(new Player3StepState){
        currState = state1;
    }
    virtual ~Rule(){}
    virtual GameField* createField() = 0;
    virtual void handle(std::string, BaseHandler*, int) = 0;
    virtual bool checkWin(GameField*, int) = 0;
    void changeState(int playersNumb)
    {
        if (playersNumb == 2){
            if (currState == state1){
                currState = state2;
                std::cout << "2-nd player\n";
            }
            else{
                currState = state1;
                std::cout << "1-nd player\n";
            }
        }
        else
            if (currState == state1){
                currState = state2;
                std::cout << "2-nd player\n";
            }
            else if (currState == state2){
                currState = state3;
                std::cout << "3-rd player\n";
            }
            else{
                currState = state1;
                std::cout << "1-st player\n";
            }
    }
};

class Rule1 : public Rule{
public:
    Rule1(){}
    GameField* createField() override
    {
        GameField* field = new GameField(10, 10, 30, 1);
        return field;
    }

    void handle(std::string commandStr, BaseHandler* handler, int playersNumb) override
    {
        currState->handle(commandStr, handler);

        if(commandStr == "attack")
            Rule::changeState(playersNumb);
    }

    bool checkWin(GameField* field, int playersNumb) override
    {
        if (playersNumb == 2){
            if (field->base1->getHealth() == 0){
                std::cout << "2-nd player won!\n";
                return true;
            }
            else if (field->base2->getHealth() == 0){
                std::cout << "1-st player won!\n";
                return true;
            }
            else {
                return false;
            }
        }
        else{
            if (field->base1->getHealth() == 0){
                std::cout << "2-nd and 3-rd players won!\n";
                return true;
            }
            else if (field->base2->getHealth() == 0){
                std::cout << "1-st and 3-rd players won!\n";
                return true;
            }
            else if (field->base3->getHealth() == 0){
                std::cout << "1-st and 2-nd players won!\n";
                return true;
            }
            else {
                return false;
            }
        }
    }
};

class Rule2 : public Rule{
public:
    Rule2(){}
    GameField* createField() override
    {
        GameField* field = new GameField(15, 15, 50, 1);
        return field;
    }

    void handle(std::string commandStr, BaseHandler* handler, int playersNumb) override
    {
        currState->handle(commandStr, handler);

        if(commandStr == "move unit")
            Rule::changeState(playersNumb);
    }

    bool checkWin(GameField* field, int playersNumb) override
    {
        if (playersNumb == 2){
            if (field->base1->getHealth() == 0){
                std::cout << "2-nd player won!\n";
                return true;
            }
            else if (field->base2->getHealth() == 0){
                std::cout << "1-st player won!\n";
                return true;
            }
            else {
                return false;
            }
        }
        else{
            if (field->base1->getHealth() == 0){
                std::cout << "2-nd and 3-rd players won!\n";
                return true;
            }
            else if (field->base2->getHealth() == 0){
                std::cout << "1-st and 3-rd players won!\n";
                return true;
            }
            else if (field->base3->getHealth() == 0){
                std::cout << "1-st and 2-nd players won!\n";
                return true;
            }
            else {
                return false;
            }
        }
    }
};
#endif // RULE_H
