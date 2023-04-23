//
// Created by Alex on 13.04.2020.
//

#ifndef GAME_FILELOG_H
#define GAME_FILELOG_H


#include <ostream>
#include <fstream>
#include "../Log.h"

class FileLog: public Log {
private:
    std::string log_message;
    std::string path;
    std::ofstream fin;
public:
    FileLog(const std::string &path);
    ~FileLog();
    friend std::ostream& operator<< (std::ostream &out, const FileLog &fileLog);
    void logMessage(const std::string &logMessage)override ;
private:
    void log();
    void setLogMessage(const std::string &logMessage);

};


#endif //GAME_FILELOG_H
