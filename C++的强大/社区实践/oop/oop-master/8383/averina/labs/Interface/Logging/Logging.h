
#ifndef OOP_LOGGING_H
#define OOP_LOGGING_H

#include "File.h"

/*
 * Logging-- класс для записи логов в консоль и файл по идиоме RAII.
 */


class Logging
{
public:
    bool isOpen();

    void loggingToFile(std::string& string);
    void loggingToConsole(std::string& string);
    void closeFile();
    void setOpen(bool status);

private:
    File* file;
    bool isFileOpen;
};




#endif //OOP_LOGGING_H
