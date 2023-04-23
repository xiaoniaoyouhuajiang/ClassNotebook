#ifndef GAME_H
#define GAME_H

#include "rule.h"
#include "gamefield.h"
#include "basehandler.h"
#include "mediator.h"
#include "loggerproxy.h"
#include "logger.h"

bool LoggerProxy::isLog = 0;
bool LoggerProxy::toFile = 0;
bool Logger::fileIsOpen = 0;
File* Logger::file = nullptr;

template <class Rule>
class GameBase
{
public:
    GameBase(){}

protected:
    GameField* field;
    BaseHandler* baseHandler;
    Mediator* mediator;
    Rule* rule;

    //CreateBaseHandler* createBaseHandler;
    CreateUnitHandler* createUnitHandler;
    MoveUnitHandler* moveUnitHandler;
    BaseStatusHandler* baseStatusHandler;
    AttackHandler* attackHandler;
    LogOnOffHandler* logHandler;
    SaveGameHandler* saveGameHandler;
    LoadGameHandler* loadGameHandler;
    WrongCommandHandler* wrongCommandHandler;

    void prepareHandlers()
    {
        this->baseHandler = new BaseHandler();
        //this->createBaseHandler = new CreateBaseHandler(this->field);
        this->createUnitHandler = new CreateUnitHandler(this->field, mediator);
        this->moveUnitHandler = new MoveUnitHandler(this->field);
        this->baseStatusHandler = new BaseStatusHandler(this->field);
        this->attackHandler = new AttackHandler(this->field, mediator);
        this->logHandler = new LogOnOffHandler();
        this->saveGameHandler = new SaveGameHandler(field);
        this->loadGameHandler = new LoadGameHandler(field, mediator);
        this->wrongCommandHandler = new WrongCommandHandler();
        //baseHandler->add(createBaseHandler);
        baseHandler->add(createUnitHandler);
        baseHandler->add(moveUnitHandler);
        baseHandler->add(baseStatusHandler);
        baseHandler->add(attackHandler);
        baseHandler->add(logHandler);
        baseHandler->add(saveGameHandler);
        baseHandler->add(loadGameHandler);
        baseHandler->add(wrongCommandHandler);
    }

    void prepareField()
    {
        this->field = new GameField();
        cout << "Turn on logging? Load the game? (nn/yy/yn) ";
        while(true){
            string str;
            getline(cin, str);
            if (str == "nn" || str == "ny" || str == "yn" || str == "yy"){
                if (str[0] == 'y'){
                    LogOnOffHandler* logOnHandler = new LogOnOffHandler();
                    logOnHandler->handle("log on");
                }
                if (str[1] == 'y'){
                    this->field = new GameField();
                    mediator = new Mediator(this->field);
                    LoadGameHandler* loadGameHandler = new LoadGameHandler(field, mediator);
                    loadGameHandler->handle("load game");
                    if (!field->isCorrectCreated)
                        break;
                    field->printAll();
                }
                break;
            }
            else{
                cout << "Wrong answer\n";
            }
        }

        if (!field->isCorrectCreated){
            this->field = rule->createField();
            this->mediator = new Mediator(this->field);
            field->printAll();
        }
    }

    void createBase(int baseNumb)
    {
        int maxUnitsCount, health, x, y;
        vector<pair<int, int>> coords;
        bool isCorrect = true;
        int baseCount = 0;

        if (!field->isBasesCreated()){      //Если базы не были созданы(загружены из сохранения)
            while (true){
                cout << "Enter: max units count, base health, x and y coordinates of base: ";
                cin >> maxUnitsCount >> health >> x >> y;
                getchar();

                if ((x <= field->getX() - 1) && (y <= field->getY() - 1) && (x >= 0) && (y >= 0) && (health > 0) && (maxUnitsCount > 0)) {
                    isCorrect = true;
                    for(pair<int, int> point: coords){
                        if (point == make_pair(x, y)){
                            cout << "Here's another base\n";
                            isCorrect = false;
                            break;
                        }
                    }
                    if (isCorrect){
                        Command* createBase = new CreateBaseCommand(field, maxUnitsCount, health, x, y);
                        createBase->execute();
                        coords.push_back(make_pair(x, y));
                        baseCount++;
                        if(baseCount == baseNumb){
                            field->printAll();
                            break;
                        }
                    }
                }
                else{
                    cout << "Wrong options\n";
                }
                field->printAll();
            }
        }
    }
};

template <class Rule, int>
class Game: public GameBase<Rule>
{
public:
    Game(){}
};

template <>
class Game<Rule1, 2>: public GameBase<Rule1>{
    Game(){}

    static Game* game;
public:
    void startGame()
    {
        this->rule = new Rule1();
        prepareField();
        prepareHandlers();
        createBase(2);

        while(true){
            string commandStr;
            cout << "Enter command:" << endl;
            getline(cin, commandStr);
            if (commandStr == "quit")
                break;
            if (commandStr == "new game"){
                LoggerProxy::offLog();
                prepareField();
                prepareHandlers();
                createBase(2);
                continue;
            }
            rule->handle(commandStr, baseHandler, 2);
            field->printAll();
            if (rule->checkWin(field, 2))
                break;
        }
        LoggerProxy::offLog();
    }

    static Game* getGame() {
            if(!game)
                game = new Game();
            return game;
    }
};

template <>
class Game<Rule2, 2>: public GameBase<Rule2>{
    Game(){}

    static Game* game;
public:
    void startGame()
    {
        this->rule = new Rule2();
        prepareField();
        prepareHandlers();
        createBase(2);

        while(true){
            string commandStr;
            cout << "Enter command:" << endl;
            getline(cin, commandStr);
            if (commandStr == "quit")
                break;
            if (commandStr == "new game"){
                LoggerProxy::offLog();
                prepareField();
                prepareHandlers();
                createBase(2);
                continue;
            }
            rule->handle(commandStr, baseHandler, 2);
            field->printAll();
            if (rule->checkWin(field, 2))
                break;
        }
        LoggerProxy::offLog();
    }

    static Game* getGame() {
            if(!game)
                game = new Game();
            return game;
    }
};

template <>
class Game<Rule1, 3>: public GameBase<Rule1>{
    Game(){}

    static Game* game;
public:
    void startGame()
    {
        this->rule = new Rule1();
        prepareField();
        prepareHandlers();
        createBase(3);

        while(true){
            string commandStr;
            cout << "Enter command:" << endl;
            getline(cin, commandStr);
            if (commandStr == "quit")
                break;
            if (commandStr == "new game"){
                LoggerProxy::offLog();
                prepareField();
                prepareHandlers();
                createBase(3);
                continue;
            }
            rule->handle(commandStr, baseHandler, 3);
            field->printAll();
            if (rule->checkWin(field, 3))
                break;
        }
        LoggerProxy::offLog();
    }

    static Game* getGame() {
            if(!game)
                game = new Game();
            return game;
    }
};

template <>
class Game<Rule2, 3>: public GameBase<Rule2>{
    Game(){}

    static Game* game;
public:
    void startGame()
    {
        this->rule = new Rule2();
        prepareField();
        prepareHandlers();
        createBase(3);

        while(true){
            string commandStr;
            cout << "Enter command:" << endl;
            getline(cin, commandStr);
            if (commandStr == "quit")
                break;
            if (commandStr == "new game"){
                LoggerProxy::offLog();
                prepareField();
                prepareHandlers();
                createBase(3);
                continue;
            }
            rule->handle(commandStr, baseHandler, 3);
            field->printAll();
            if (rule->checkWin(field, 3))
                break;
        }
        LoggerProxy::offLog();
    }

    static Game* getGame() {
            if(!game)
                game = new Game();
            return game;
    }
};
#endif // GAME_H
