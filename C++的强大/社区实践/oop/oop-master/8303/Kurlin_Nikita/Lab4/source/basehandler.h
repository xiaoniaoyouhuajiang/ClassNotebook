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

    virtual void handle(string command){
        this->next->handle(command);
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
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "create unit"){
            cout << "Choose base for creating unit (1 or 2) ";
            string str;
            getline(cin, str);

            if (str == "1" || str == "2"){
                int baseNumb = (str == "1") ? 1 : 2;
                int n = (baseNumb == 1) ? field->base1->getCapacityCount() : field->base2->getCapacityCount();
                if (n == 0)
                    cout << "Max count of unit on base\n";

                Command* createUnit = new CreateUnitCommand(field, mediator, n, baseNumb);
                createUnit->execute();
            }
            else {
                cout << "Wrong numb of base\n";
            }
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

class WrongCommandHandler : public BaseHandler{

public:
    void handle(string command) override{
        cout << "\nThe command doesn't exist!\n";
   }
};

class MoveUnitHandler : public BaseHandler{

public:
    MoveUnitHandler(GameField* field) : BaseHandler(field) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "move unit"){
            cout << "Choose base for moving unit (1 or 2) ";
            string str;
            getline(cin, str);

            Unit* currUnit;
            Point* currPoint;
            Base* base = (str == "1") ? field->base1 : field->base2;
            if (str == "1" || str == "2"){
                while(true){
                    currUnit = (str == "1") ? field->base1->getCurrUnit() : field->base2->getCurrUnit();
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
            else {
                cout << "Wrong numb of base\n";
            }
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

class BaseStatusHandler : public BaseHandler{

public:
    BaseStatusHandler(GameField* field) : BaseHandler(field) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "base status"){
            cout << "Choose base for status (1 or 2) ";
            Base* currBase;
            string str;
            getline(cin, str);

            if (str == "1" || str == "2"){
                int baseNumb = (str == "1") ? 1 : 2;
                currBase = (baseNumb == 1) ? field->base1 : field->base2;
                Command* baseStatus = new BaseStatusCommand(field, currBase, baseNumb);
                baseStatus->execute();
            }
            else {
                cout << "Wrong numb of base\n";
            }
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

class AttackHandler : public BaseHandler{

public:
    AttackHandler(GameField* field, Mediator* mediator) : BaseHandler(field, mediator) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "attack"){
            cout << "Choose base for attack (1 or 2) ";
            Unit* currUnit;
            Point* currPoint;
            string str;
            getline(cin, str);

            if (str == "1" || str == "2"){
                int baseNumb = (str == "1") ? 1 : 2;
                while(true){
                    currUnit = (baseNumb == 1) ? field->base1->getCurrUnit() : field->base2->getCurrUnit();
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
            else {
                cout << "Wrong numb of base\n";
            }
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

class LogOnOffHandler : public BaseHandler{

public:
    LogOnOffHandler(){}
    void handle(string command) override{
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
            BaseHandler::handle(command);
        }
    }

};

class SaveGameHandler : public BaseHandler{

public:
    SaveGameHandler(GameField* field) : BaseHandler(field) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "save game"){
            Command* saveGame = new SaveGameCommand(field);
            saveGame->execute();
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

class LoadGameHandler : public BaseHandler{

public:
    LoadGameHandler(GameField* field, Mediator* mediator) : BaseHandler(field, mediator) {}
    void handle(string command) override{
        transform(command.begin(), command.end(), command.begin(), tolower);
        if (command == "load game"){
            Command* loadGame = new LoadGameCommand(field, mediator);
            loadGame->execute();
            mediator->updateField(field);
        }
        else{
            BaseHandler::handle(command);
        }
   }
};

#endif // BASEHANDLER_H
