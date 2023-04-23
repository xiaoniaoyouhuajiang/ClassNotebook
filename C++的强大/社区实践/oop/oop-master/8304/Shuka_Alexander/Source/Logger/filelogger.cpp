#include "filelogger.h"


FileLogger::FileLogger(const std::string& fileName)
{
    this->fileName = fileName;
}


void FileLogger::writeToLog(const std::string& msg, LVL lvl)
{
    std::ofstream file(fileName, std::ios::app);

    if (!file.is_open()) {
        return;
    }

    file << getMsgLvl(lvl) + " " + msg + "\n";
    file.close();
}



