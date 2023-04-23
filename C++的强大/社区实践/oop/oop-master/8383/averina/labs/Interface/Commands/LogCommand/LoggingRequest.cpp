
#include "LoggingRequest.h"


void LoggingRequest::Command()
{
    std::string input;
    std::cout << "-------- LOGGING -------" << std::endl;
    std::cout << "/console" << std::endl;
    std::cout << "/file" << std::endl;
    std::cout << "/off" << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "<command> : " ;
    std::cin >> input;
    if (input == "/off")
    {
        field->logging->logOff();
        std::cout << "logging off" << std::endl;
    }
    else if (input == "/console")
    {
        field->logging->logInConsole();
        std::cout << "switch to logging in console" << std::endl;
    }
    else if (input == "/file")
    {
        field->logging->logInFile();
        std::cout << "switch to logging in file" << std::endl;
    }
    else
    {
        std::cout << "ERROR: wrong command of logging" << std::endl;
    }

}