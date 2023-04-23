#ifndef OOP_GAMECLASS_H
#define OOP_GAMECLASS_H

#include "../Field/Field.h"
#include "../Interface/Links/Chain.h"
#include "../Interface/Links/SaveLinks/GameSaveLink.h"
#include "../Interface/Links/LogLinks/LoggingLink.h"
#include "../Interface/Links/BaseLinks/BaseInfoLink.h"
#include "../Interface/Links/UnitLinks/CreateUnitLink.h"
#include "../Interface/Links/UnitLinks/GetUnitLink.h"
#include "../Interface/Links/UnitLinks/AttackUnitLink.h"
#include "../Interface/Links/UnitLinks/MoveUnitLink.h"
#include "../Interface/Links/UnknownLink.h"
#include "../Interface/Links/SkipLink.h"


template <typename T, size_t n>
class GameClass;

template <typename T>
class GameClass<T, 2>
{
private:
    Field* field;
    Chain* command;
    T rule;
public:
    void createGame()
    {
        std::cout << "-------- GAME FIELD -------" << std::endl;
        rule.numberOfPlayers = 2;
        field = rule.createField(2);

        field->show('M');

        command = new Chain();

        command->addNext(new GameSaveLink(field));
        command->addNext(new LoggingLink(field));
        command->addNext(new BaseInfoLink(field));
        command->addNext(new GetUnitLink(field));
        command->addNext(new CreateUnitLink(field));
        command->addNext(new MoveUnitLink(field));
        command->addNext(new AttackUnitLink(field));
        command->addNext(new SkipLink(field));
        command->addNext(new UnknownLink(field));
    }

    void playGame()
    {
        std::string commandStr;
        int result = -1;
        while (result < 0)
        {
            //cls;
            std::cout << rule.getState() << ", your move!"<< std::endl;
            std::cout << "--------- COMMANDS ----------" << std::endl;
            std::cout << "/saveload" << std::endl;
            std::cout << "/new" << std::endl;
            std::cout << "/logging" << std::endl;
            std::cout << "/info" << std::endl;
            std::cout << "/create" << std::endl;
            std::cout << "/get " << std::endl;
            std::cout << "/move" << std::endl;
            std::cout << "/attack" << std::endl;
            std::cout << "/skip " << std::endl;
            std::cout << "/quit " << std::endl;
            std::cout << "------------------------------" << std::endl;
            std::cout << "<command> : ";
            std::cin >> commandStr;

            if (commandStr == "/quit") break;
            else if (commandStr == "/new")
            {
                delete field;
                createGame();
            }
            else rule.playerCommand(commandStr, command);
            field->show(rule.getState());
            result = rule.isLose(field);
        }
        if (result == 0)
        {
            std::cout << "The Bright Kingdom has fallen.. \n"
                         "Glory to the forces of darkness!" << std::endl;
        }
        if (result == 1)
        {
            std::cout << "The Dark Kingdom has fallen..\n"
                         "Light will conquer all darkness!" << std::endl;
        }
    }
};

template <typename T>
class GameClass<T, 3>
{
private:
    Field* field;
    Chain* command;
    T rule;
public:
    void createGame()
    {
        std::cout << "-------- GAME FIELD -------" << std::endl;
        rule.numberOfPlayers = 3;
        field = rule.createField(3);

        field->show('M');

        command = new Chain();

        command->addNext(new GameSaveLink(field));
        command->addNext(new LoggingLink(field));
        //command->addNext(new CreateBaseLink(field));
        command->addNext(new BaseInfoLink(field));
        command->addNext(new GetUnitLink(field));
        command->addNext(new CreateUnitLink(field));
        command->addNext(new MoveUnitLink(field));
        command->addNext(new AttackUnitLink(field));
        command->addNext(new SkipLink(field));
        command->addNext(new UnknownLink(field));
    }

    void playGame()
    {
        std::string commandStr;
        int result = -1;
        int players = 3;
        while (result < 0 && players != 1)
        {
            //cls;
            std::cout << rule.getState() << ", your move!"<< std::endl;
            std::cout << "========= COMMANDS ========" << std::endl;
            std::cout << "----------- game ----------" << std::endl;
            //std::cout << "/saveload" << std::endl;
            std::cout << "/new" << std::endl;
            std::cout << "/logging" << std::endl;
            std::cout << "----------- base ----------" << std::endl;
            std::cout << "/info" << std::endl;
            std::cout << "/create" << std::endl;
            std::cout << "/get " << std::endl;
            std::cout << "----------- units ---------" << std::endl;
            std::cout << "/move" << std::endl;
            std::cout << "/attack" << std::endl;
            std::cout << "---------- other ----------" << std::endl;
            std::cout << "/skip " << std::endl;
            std::cout << "/quit " << std::endl;
            std::cout << "===========================" << std::endl;
            std::cout << "<command> : ";
            std::cin >> commandStr;

            if (commandStr == "/quit") break;
            if (commandStr == "/new")
            {
                delete field;
                createGame();
            }
            else
            {
                rule.playerCommand(commandStr, command);
            }
            field->show(rule.getState());
            result = rule.isLose(field);
            if (result == 0)
            {
                std::cout << "The Bright Kingdom has fallen.. \n"
                             "Glory to the forces of darkness!" << std::endl;
                players--;
            }
            if (result == 1)
            {
                std::cout << "The Dark Kingdom has fallen..\n"
                             "Light will conquer all darkness!" << std::endl;
                players--;
            }
            if (result == 2)
            {
                std::cout << "The Undead Kindom has fallen..\n"
                             "There they belong" << std::endl;
                players--;
            }
        }
    }
};

#endif //OOP_GAMECLASS_H
