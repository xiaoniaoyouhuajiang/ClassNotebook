//
// Created by Alex on 13.04.2020.
//

#ifndef GAME_PROXYLOGGER_H
#define GAME_PROXYLOGGER_H

#include <string>
#include <memory>
#include "../Log.h"
#include "../TerminalLog/TerminalLog.h"
#include "../FileLog/FileLog.h"

class ProxyLogger : Log {
private:
    std::unique_ptr<TerminalLog> terminalLog;
    std::unique_ptr<FileLog> fileLog;
    bool isWriteLog;
    bool isWriteInTerminal;
    bool isWriteInFile;
public:
    ProxyLogger();
    void logMessage(const std::string &logMessage) override;
    void enableTerminalWriteMode();
    void enableFileWriteLogMode();
    void enableWrite();
    void disableWrite();
    void switchWriteMode();
};


#endif //GAME_PROXYLOGGER_H
