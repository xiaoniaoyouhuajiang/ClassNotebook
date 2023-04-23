//
// Created by Artem Butko on 20/05/2020.
//

#include "Facade.h"


void Facade::createGame()
{
    std::cout << "-------- GAME FIELD -------" << std::endl;
    field = new Field(10, 10);
    field->show();

    command = new Chain();
    command->addNext(new GameSaveLink(field));
    command->addNext(new LoggingLink(field));
    command->addNext(new CreateBaseLink(field));
    command->addNext(new BaseInfoLink(field));
    command->addNext(new CreateUnitLink(field));
    command->addNext(new GetUnitLink(field));
    command->addNext(new MoveUnitLink(field));
    command->addNext(new AttackUnitLink(field));
    command->addNext(new UnknownLink(field));
}

void Facade::playGame()
{
    std::string command;
    while (true)
    {
        std::cout << "------ GAME COMMANDS ------" << std::endl;
        std::cout << "/game" << std::endl;
        std::cout << "/logging" << std::endl;
        std::cout << "/create_base" << std::endl;
        std::cout << "/info_base" << std::endl;
        std::cout << "/create_unit " << std::endl;
        std::cout << "/get_unit " << std::endl;
        std::cout << "/move_unit " << std::endl;
        std::cout << "/attack_unit " << std::endl;
        std::cout << "/quit " << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "<command> : ";
        std::cin >> command;
        if (command == "/quit") break;
        this->command->chain(command);
        field->show();
    }
}
