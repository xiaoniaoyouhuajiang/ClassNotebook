//
// Created by Alex on 13.04.2020.
//

#ifndef GAME_TERMINALLOG_H
#define GAME_TERMINALLOG_H


#include <ostream>
#include "../Log.h"

class TerminalLog : public Log {
private:
    std::string log_message;
public:
    friend std::ostream& operator<< (std::ostream &out, const TerminalLog &terminalLog);
    void logMessage(const std::string &logMessage) override;
private:
    void setLogMessage(const std::string &logMessage);
    void log ();
};


#endif //GAME_TERMINALLOG_H
