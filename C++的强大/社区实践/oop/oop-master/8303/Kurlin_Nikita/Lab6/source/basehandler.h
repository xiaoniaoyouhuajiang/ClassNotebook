#ifndef BASEHANDLER_H
#define BASEHANDLER_H

#include <string>
#include <algorithm>
#include "base.h"
#include "gamefield.h"
#include "command.h"
#include "loggerproxy.h"

using namespace std;

class BaseHandler{

    BaseHandler* next;

protected:
    GameField* field;
    Mediator* mediator;
    BaseHandler(GameField* field) : next(nullptr), field(field){}
    BaseHandler(GameField* field, Mediator* mediator) : next(nullptr), field(field), mediator(mediator){}

public:
    BaseHandler() : next(nullptr) {}

    void setNext(BaseHandler* next){
        this->next = next;
    }

    void add(BaseHandler* next){
        if (this->next)
            this->next->add(next);
        else
            this->next = next;
    }

    virtual void handle(string command, int playerNumb){
        this->next->handle(command, playerNumb);
    }

    virtual ~BaseHandler(){}
};

/*class CreateBaseHandler : public BaseHandler{

public:
    CreateBaseHandler(GameField* field) : BaseHandler(field) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "create base"){
            int maxUnitsCount, health, x, y;

            cout << "Enter: max units count, base health, x and y coordinates of base: ";
            cin >> maxUnitsCount >> health >> x >> y;
            getchar();

            if ((field->base1 == nullptr) || (field->base2 == nullptr)){
                Command* createBase = new CreateBaseCommand(field, maxUnitsCount, health, x, y);
                createBase->execute();
            }
            else {
                cout << "There are two base already\n";
            }
        }
        else{
            BaseHandler::handle(command);
        }
   }
};*/

class CreateUnitHandler : public BaseHandler{

public:
    CreateUnitHandler(GameField* field, Mediator* mediator) : BaseHandler(field, mediator) {}
    void handle(string command, int playerNumb) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "create unit"){
            //cout << "Choose base for creating unit (1 or 2) ";
            //string str;
            //getline(cin, str);

            //if (str == "1" || str == "2"){
                int baseNumb = playerNumb;// (str == "1") ? 1 : 2;
                int n;
                if (baseNumb == 1)
                    n = field->base1->getCapacityCount();
                else if (baseNumb == 2)
                    n = field->base2->getCapacityCount();
                else {
                    n = field->base3->getCapacityCount();
                }
                if (n == 0)
                    cout << "Max count of unit on base\n";

                Command* createUnit = new CreateUnitCommand(field, mediator, n, baseNumb);
                createUnit->execute();
            //}
            //else {
             //   cout << "Wrong numb of base\n";
            //}
        }
        else{
            BaseHandler::handle(command, playerNumb);
        }
   }
};

class WrongCommandHandler : public BaseHandler{

public:
    void handle(string command, int playerNumb) override{
        cout << "\nThe command doesn't exist!\n";
   }
};

class MoveUnitHandler : public BaseHandler{

public:
    MoveUnitHandler(GameField* field) : BaseHandler(field) {}
    void handle(string command, int playerNumb) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "move unit"){
            //cout << "Choose base for moving unit (1 or 2) ";
            //string str;
            //getline(cin, str);

            Unit* currUnit;
            Point* currPoint;
            Base* base;
            if (playerNumb == 1)
                base = field->base1;
            else if (playerNumb == 2)
                base = field->base2;
            else
                base = field->base3;

            while(true){
                if (playerNumb == 1)
                    currUnit = field->base1->getCurrUnit();
                else if (playerNumb == 2)
                    currUnit = field->base2->getCurrUnit();
                else
                    currUnit = field->base3->getCurrUnit();

                currPoint = field->findUnit(currUnit);
                cout << currUnit->getName() << " (" << currPoint->x << ";" << currPoint->y << ") ? ";

                string str;
                getline(cin, str);

                if(str == "n")
                    continue;
                else{
                    if(str == "w" || str == "s" || str == "a" || str == "d"){
                        Command* moveUnit = new MoveUnitCommand(field, str, base, currUnit);
                        moveUnit->execute();
                    }
                    else{
                        cout << "Wrong command for moving\n";
                        return;
                    }
                    break;
                }
            }
        }
        else{
            BaseHandler::handle(command, playerNumb);
        }
   }
};

class BaseStatusHandler : public BaseHandler{

public:
    BaseStatusHandler(GameField* field) : BaseHandler(field) {}
    void handle(string command, int playerNumb) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "base status"){
            //cout << "Choose base for status (1 or 2) ";
            Base* currBase;
            //string str;
            //getline(cin, str);

            if (playerNumb == 1)
                currBase = field->base1;
            else if (playerNumb == 2)
                currBase = field->base2;
            else
                currBase = field->base3;

            Command* baseStatus = new BaseStatusCommand(field, currBase, playerNumb);
            baseStatus->execute();
        }
        else{
            BaseHandler::handle(command, playerNumb);
        }
   }
};

class AttackHandler : public BaseHandler{

public:
    AttackHandler(GameField* field, Mediator* mediator) : BaseHandler(field, mediator) {}
    void handle(string command, int playerNumb) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "attack"){
            //cout << "Choose base for attack (1 or 2) ";
            Unit* currUnit;
            Point* currPoint;
            //string str;
            //getline(cin, str);

            while(true){
                if (playerNumb == 1)
                    currUnit = field->base1->getCurrUnit();
                else if (playerNumb == 2)
                    currUnit = field->base2->getCurrUnit();
                else
                    currUnit = field->base3->getCurrUnit();

                currPoint = field->findUnit(currUnit);
                cout << currUnit->getName() << " (" << currPoint->x << ";" << currPoint->y << ") ? ";

                string str;
                getline(cin, str);

                if(str == "n")
                    continue;
                else{
                    if(str == "w" || str == "s" || str == "a" || str == "d"){
                        Command* Attack = new AttackCommand(field, mediator, str, currUnit, currPoint);
                        Attack->execute();
                    }
                    else{
                        cout << "Wrong direction of attack\n";
                        return;
                    }
                    break;
                }
            }
        }
        else{
            BaseHandler::handle(command, playerNumb);
        }
   }
};

class LogOnOffHandler : public BaseHandler{

public:
    LogOnOffHandler(){}
    void handle(string command, int playerNumb = 0) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "log on" || command == "log off"){
            if (LoggerProxy::isOn()){
                LogOnOffCommand* logOff = new LogOnOffCommand(field, "off");
                logOff->execute();
                return;
            }
            else{
                string answer;
                cout << "to file? ";
                getline(cin, answer);

                if(answer == "y" || answer == "n"){
                    LogOnOffCommand* logOn = new LogOnOffCommand(field, (answer == "y") ? "toFile" : "toConsole");
                    logOn->execute();
                }
                else{
                    cout << "Wrong answer\n";
                    return;
                }
            }
        }
        else{
            BaseHandler::handle(command, playerNumb);
        }
    }

};

class SaveGameHandler : public BaseHandler{

public:
    SaveGameHandler(GameField* field) : BaseHandler(field) {}
    void handle(string command, int playerNumb = 0) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "save game"){
            Command* saveGame = new SaveGameCommand(field);
            saveGame->execute();
        }
        else{
            BaseHandler::handle(command, playerNumb);
        }
   }
};

class LoadGameHandler : public BaseHandler{

public:
    LoadGameHandler(GameField* field, Mediator* mediator) : BaseHandler(field, mediator) {}
    void handle(string command, int playerNumb = 0) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "load game"){
            Command* loadGame = new LoadGameCommand(field, mediator);
            loadGame->execute();
            mediator->updateField(field);
        }
        else{
            BaseHandler::handle(command, playerNumb);
        }
   }
};

#endif // BASEHANDLER_H
