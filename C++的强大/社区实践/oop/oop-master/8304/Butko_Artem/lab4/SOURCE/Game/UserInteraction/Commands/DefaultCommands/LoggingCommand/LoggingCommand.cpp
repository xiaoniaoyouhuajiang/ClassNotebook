//
// Created by Artem Butko on 21.05.2020.
//

#include "LoggingCommand.h"
#include "../../../Logging/LoggingProxy/LoggingProxy.h"

void LoggingCommand::Command()
{
    std::string input;
    std::cout << "-------- LOGGING -------" << std::endl;
    std::cout << "/console" << std::endl;
    std::cout << "/file" << std::endl;
    std::cout << "/off" << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cin >> input;
    if (input == "/off")
    {
        field->logging->loggingOff();
        std::cout << "logging off" << std::endl;
    }
    else if (input == "/console")
    {
        field->logging->loggingInConsole();
        std::cout << "switch to logging in console" << std::endl;
    }
    else if (input == "/file")
    {
        field->logging->loggingInFile();
        std::cout << "switch to logging in file" << std::endl;
    }
    else
    {
       std::cout << "ERROR: wrong command of logging" << std::endl;
    }

}
