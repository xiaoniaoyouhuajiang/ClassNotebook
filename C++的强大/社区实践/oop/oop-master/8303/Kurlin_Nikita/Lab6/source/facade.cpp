#include "facade.h"

/*bool LoggerProxy::isLog = 0;
bool LoggerProxy::toFile = 0;
bool Logger::fileIsOpen = 0;
File* Logger::file = nullptr;

Facade::Facade()
{

}

void Facade::prepareGame()
{
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
                startGame();
                return;
            }
            break;
        }
        else{
            cout << "Wrong answer\n";
        }
    }


    //Game field creation
    int unitMax, xx, yy;

    while (true){
        cout << "Please, enter the max numb of units on game field: ";
        cin >> unitMax;
        if (unitMax <= 1){
            cout << "Incorrect count\n";
            continue;
        }
        while (true){
            cout << "Enter size of field (x y): \n";
            cin >> xx >> yy;
            if (xx <= 1 || yy <= 1)
                cout << "Incorrect size\n";
            else
                break;
        }
        break;
    }
    getchar();
    this->field = new GameField(xx, yy, unitMax, true);
    field->printAll();

    //Base creation
    int maxUnitsCount, health, x, y;
    int baseCount = 0;
    int baseX = -1;
    int baseY = -1;

    while (true){
        cout << "Enter: max units count, base health, x and y coordinates of base: ";
        cin >> maxUnitsCount >> health >> x >> y;
        getchar();

        if ((x <= xx - 1) && (y <= yy - 1) && (x >= 0) && (y >= 0) && (health > 0) && (maxUnitsCount > 0)) {
            if (x != baseX || y != baseY){
                Command* createBase = new CreateBaseCommand(field, maxUnitsCount, health, x, y);
                createBase->execute();
                baseX = x;
                baseY = y;
                baseCount++;
                if(baseCount == 2)
                    break;
            }
            else {
                cout << "Here's another base\n";
            }
        }
        else{
            cout << "Wrong options\n";
        }
        field->printAll();
    }
    field->printAll();

    mediator = new Mediator(this->field);

    startGame();
}

void Facade::startGame()
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

    while(true){
        string commandStr;
        cout << "Enter command:" << endl;
        getline(cin, commandStr);
        if (commandStr == "quit")
            break;
        baseHandler->handle(commandStr);
        field->printAll();
    }
    LoggerProxy::offLog();
}*/
