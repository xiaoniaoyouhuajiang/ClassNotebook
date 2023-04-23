//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_GAMECLASS_H
#define OOP_NEW_GAMECLASS_H
#define esc 27
#define cls printf("%c[2J",esc)

#include "../../GameField/Field/Field.h"
#include "../ChainOfResponsibility/Chain.h"
#include "../ChainOfResponsibility/CreateBaseLink/CreateBaseLink.h"
#include "../ChainOfResponsibility/BaseInfoLink/BaseInfoLink.h"
#include "../ChainOfResponsibility/CreateUnitLink/CreateUnitLink.h"
#include "../ChainOfResponsibility/GetUnitLink/GetUnitLink.h"
#include "../ChainOfResponsibility/MoveUnitLink/MoveUnitLink.h"
#include "../ChainOfResponsibility/AttackUnitLink/AttackUnitLink.h"
#include "../ChainOfResponsibility/UnknownLink/UnknownLink.h"
#include "../ChainOfResponsibility/LoggingLink/LoggingLink.h"
#include "../ChainOfResponsibility/GameSaveLink/GameSaveLink.h"
/*
 * GameClass -- класс, реализующий паттерн "Фасад".
 */
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
        //command->addNext(new CreateBaseLink(field));
        command->addNext(new BaseInfoLink(field));
        command->addNext(new CreateUnitLink(field));
        command->addNext(new GetUnitLink(field));
        command->addNext(new MoveUnitLink(field));
        command->addNext(new AttackUnitLink(field));
        command->addNext(new UnknownLink(field));
    }

    void playGame()
    {
        std::string commandStr;
        int result = -1;
        while (result < 0)
        {
            //cls;
            field->show(rule.getState());
            std::cout << rule.getState() << ", your move!"<< std::endl;
            std::cout << "------ GAME COMMANDS ------" << std::endl;
            //std::cout << "/game" << std::endl;
            std::cout << "/new_game" << std::endl;
            std::cout << "/logging" << std::endl;
            std::cout << "/info_base" << std::endl;
            std::cout << "/create_unit " << std::endl;
            std::cout << "/get_unit " << std::endl;
            std::cout << "/move_unit " << std::endl;
            std::cout << "/attack_unit " << std::endl;
            std::cout << "/quit " << std::endl;
            std::cout << "/skip " << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "<command> : ";
            std::cin >> commandStr;
            if (commandStr == "/quit") break;
            if (commandStr == "/new_game")
            {
                delete field;
                createGame();
            }
            else
            {
                rule.playerCommand(commandStr, command);
            }
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
        command->addNext(new CreateUnitLink(field));
        command->addNext(new GetUnitLink(field));
        command->addNext(new MoveUnitLink(field));
        command->addNext(new AttackUnitLink(field));
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
            std::cout << "------ GAME COMMANDS ------" << std::endl;
           // std::cout << "/game" << std::endl;
            std::cout << "/new_game" << std::endl;
            std::cout << "/logging" << std::endl;
            std::cout << "/info_base" << std::endl;
            std::cout << "/create_unit " << std::endl;
            std::cout << "/get_unit " << std::endl;
            std::cout << "/move_unit " << std::endl;
            std::cout << "/attack_unit " << std::endl;
            std::cout << "/quit " << std::endl;
            std::cout << "/skip " << std::endl;
            std::cout << "---------------------------" << std::endl;
            std::cout << "<command> : ";
            std::cin >> commandStr;
            if (commandStr == "/quit") break;
            if (commandStr == "/new_game")
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
#endif //OOP_NEW_GAMECLASS_H
