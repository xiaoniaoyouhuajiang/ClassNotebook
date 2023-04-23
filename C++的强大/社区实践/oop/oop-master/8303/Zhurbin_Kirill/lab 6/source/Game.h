#ifndef OOP1_GAME_H
#define OOP1_GAME_H

#include "Rules.h"
#include "Field.h"
#include "Mediator.h"
#include "Handler.h"

template <typename T>
class GameBase{
protected:
    Field* field;
    Mediator* mediator;
    BaseHandler* baseHandler;
    BaseHandler* setBase;
    BaseHandler* noCommand;
    BaseHandler* setUnit;
    BaseHandler* moveUnit;
    BaseHandler* statusBase;
    BaseHandler* attackUnit;
    BaseHandler* switchLogMode;
    BaseHandler* save;
    BaseHandler* load;
    Adapter* adapter;
    int loser;
    std::string commandStr;


protected:
    void createGame(Adapter* adapter){
        mediator = new Mediator(field);
        baseHandler = new BaseHandler();
        setBase = new SetBaseHandler(field, adapter);
        noCommand = new NoCommandHandler();
        setUnit = new SetUnitHandler(field, mediator, adapter);
        moveUnit = new MoveUnitHandler(field);
        statusBase = new StatusBaseHandler(field);
        attackUnit = new AttackUnitHandler(field);
        switchLogMode = new SwitchLogHandler(adapter);
        save = new SaveHandler(field);
        load = new LoadHandler(field, mediator);
        baseHandler->add(setBase);
        baseHandler->add(statusBase);
        baseHandler->add(moveUnit);
        baseHandler->add(setUnit);
        baseHandler->add(attackUnit);
        baseHandler->add(switchLogMode);
        baseHandler->add(save);
        baseHandler->add(load);
        baseHandler->add(noCommand);

        std::cout << "Game preparation done, you can start playing" << std::endl;
    }

    void createBase(int countBase){
        std::cout << "Load game or new game?" << std::endl;
        std::cin >> commandStr;
        if (commandStr == "load") {
            baseHandler->handle("load", 1);
            std::cout << "-----------------------------------" << std::endl;
            field->printLandscape();
            std::cout << "-----------------------------------" << std::endl;
            field->printAll();
        }

        else{
            std::cout << "-----------------------------------" << std::endl;
            field->printLandscape();
            std::cout << "-----------------------------------" << std::endl;
            field->printNeutral();

            std::cout << "User 1 set base: " << std::endl;
            baseHandler->handle("setBase", 1);
            std::cout << "User 2 set base: " << std::endl;
            baseHandler->handle("setBase", 1);
            if (countBase == 3) {
                std::cout << "User 3 set base: " << std::endl;
                baseHandler->handle("setBase", 1);
            }
            field->printAll();
        }
    }


};

template <typename RuleBase, int>
class Game: public GameBase<RuleBase>{

};

template<>
class Game<Rule1, 2>: public GameBase<Rule1>{
    Adapter* adapter;
    Rule1* rule;
    static Game<Rule1, 2> *game;


private:
    Game<Rule1, 2>(){

    }

public:

    static Game<Rule1, 2>* getInstance(){
        if (game == nullptr)
            game = new Game<Rule1, 2>;
        return game;
    }

    void createGame(){
        adapter = new Adapter();
        rule = new Rule1();
        this->field = rule->createField(adapter);
        GameBase::createGame(adapter);
    }

    void play(){
        GameBase::createBase(2);
        while (true) {
            loser = rule->isLose(field, 2);
            if (!loser) {
                std::cin >> commandStr;
                if (commandStr == "newGame"){
                    delete this->field;
                    this->field = rule->createField(adapter);
                    GameBase::createBase(2);
                }
                rule->handle(commandStr, 2, baseHandler);
                field->printAll();
            }

            else{
                if (loser == 1){
                    std::cout << "Player 1 lose!" << std::endl;
                    break;
                }
                else if (loser == 2){
                    std::cout << "Player 2 lose!" << std::endl;
                    break;
                }
            }
        }
    }
};

template<>
class Game<Rule2, 2>: public GameBase<Rule2>{
    Adapter* adapter;
    Rule2* rule;

private:
    Game<Rule2, 2>(){

    }

    static Game<Rule2, 2> *game;

public:

    static Game<Rule2, 2>* getInstance(){
        if (game == nullptr)
            game = new Game<Rule2, 2>;
        return game;
    }

    void createGame(){
        adapter = new Adapter();
        rule = new Rule2();
        this->field = rule->createField(adapter);
        GameBase::createGame(adapter);
    }

    void play(){
        GameBase::createBase(2);
        int countMove = 0;
        while (true) {
            loser = rule->isLose(countMove, field);
            if (!loser) {
                std::cin >> commandStr;
                if (commandStr == "newGame"){
                    delete this->field;
                    this->field = rule->createField(adapter);
                    GameBase::createBase(2);
                }
                rule->handle(commandStr, 2, baseHandler);
                field->printAll();
            }
            else{
                if (loser == 1){
                    std::cout << "Player 1 lose!" << std::endl;
                    break;
                }
                else if (loser == 2){
                    std::cout << "Player 2 lose!" << std::endl;
                    break;
                }

            }
            countMove++;
        }

    }

};

template<>
class Game<Rule1, 3>: public GameBase<Rule1>{
    Adapter* adapter;
    Rule1* rule;

private:
    Game<Rule1, 3>(){

    }

    static Game<Rule1, 3> *game;

public:

    static Game<Rule1, 3>* getInstance(){
        if (game == nullptr)
            game = new Game<Rule1, 3>;
        return game;
    }

    void createGame(){
        adapter = new Adapter();
        rule = new Rule1();
        this->field = rule->createField(adapter);
        GameBase::createGame(adapter);
    }

    void play(){
        GameBase::createBase(3);
        while (true) {
            loser = rule->isLose(field, 3);
            if (!loser) {
                std::cin >> commandStr;
                if (commandStr == "newGame"){
                    delete this->field;
                    this->field = rule->createField(adapter);
                    GameBase::createBase(3);
                }
                rule->handle(commandStr, 3, baseHandler);
                field->printAll();
            }

            else{
                if (loser == 1){
                    std::cout << "Player 1 lose!" << std::endl;
                    break;
                }
                else if (loser == 2){
                    std::cout << "Player 2 lose!" << std::endl;
                    break;
                }
                else if (loser == 3){
                    std::cout << "Player 3 lose!" << std::endl;
                    break;
                }
            }
        }
    }
};

template<>
class Game<Rule2, 3>: public GameBase<Rule2>{
    Adapter* adapter;
    Rule2* rule;

private:
    Game<Rule2, 3>(){

    }

    static Game<Rule2, 3> *game;

public:

    static Game<Rule2, 3>* getInstance(){
        if (game == nullptr)
            game = new Game<Rule2, 3>;
        return game;
    }

    void createGame(){
        adapter = new Adapter();
        rule = new Rule2();
        this->field = rule->createField(adapter);
        GameBase::createGame(adapter);
    }

    void play(){
        GameBase::createBase(3);
        int countMove = 0;
        while (true) {
            loser = rule->isLose(countMove, field);
            if (!loser) {
                std::cin >> commandStr;
                if (commandStr == "newGame"){
                    delete this->field;
                    this->field = rule->createField(adapter);
                    GameBase::createBase(3);
                }
                rule->handle(commandStr, 3, baseHandler);
                field->printAll();
            }
            else{
                if (loser == 1){
                    std::cout << "Player 1 lose!" << std::endl;
                    break;
                }
                else if (loser == 2){
                    std::cout << "Player 2 and 3 lose!" << std::endl;
                    break;
                }

            }
            countMove++;
        }

    }

};


#endif //OOP1_GAME_H
