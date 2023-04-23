
#include <string>
#include <iostream>
#include "Logging.h"
#include "File.h"

bool Logging::isOpen()
{
    return isFileOpen;
}

void Logging::loggingToFile(std::string& string)
{
    if (!isFileOpen)
    {
        file = new File("game_logging.txt", "save");
        isFileOpen = true;
    }
    file->writeString(&string[0]);
}

void Logging::loggingToConsole(std::string &string)
{
    std::cout << string << std::endl;
}

void Logging::closeFile()
{
    file->~File();
}

void Logging::setOpen(bool openStatus)
{
    isFileOpen = openStatus;
}