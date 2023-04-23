#include "logger.h"

Logger::Logger()
{

}

void Logger::printLogConsole(std::string &str)
{
    std::cout << str;
}

void Logger::printLogFile(std::string &str)
{
    if (!fileIsOpen){
        file = new File("Log.txt");
        fileIsOpen = true;
    }
    file->write(&str[0]);
}
