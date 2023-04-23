#include "filelog.hpp"

FileLog::FileLog(const std::string& fileName)
{
    this->fileName = fileName;
}


void FileLog::writeTo(const std::string& msg, TYPE type)
{
    std::ofstream file(fileName, std::ios::app);

    if (!file.is_open()) {
        return;
    }

    file << getMessageType(type) + " " + msg + "\n";
    file.close();
}
