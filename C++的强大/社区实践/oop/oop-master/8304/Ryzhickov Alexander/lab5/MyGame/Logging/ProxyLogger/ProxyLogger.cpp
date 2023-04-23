//
// Created by Alex on 13.04.2020.
//
#include "ProxyLogger.h"

#include <memory>


void ProxyLogger::logMessage(const std::string &logMessage) {
    if (isWriteLog){
        if (isWriteInTerminal){
            terminalLog->logMessage(logMessage);
        }
        if (isWriteInFile){
            fileLog->logMessage(logMessage);
        }

    }
}

ProxyLogger::ProxyLogger() {
    isWriteLog = true;
    isWriteInTerminal = true;
    isWriteInFile = false;
    terminalLog = std::make_unique<TerminalLog>();
    fileLog = std::make_unique<FileLog>("C:\\Users\\Alex\\Desktop\\out.txt");
}

void ProxyLogger::enableTerminalWriteMode() {
    isWriteInFile = false;
    isWriteInTerminal = true;
}

void ProxyLogger::enableFileWriteLogMode() {
    isWriteInFile = true;
    isWriteInTerminal = false;
}

void ProxyLogger::enableWrite() {
    isWriteLog = true;
}

void ProxyLogger::disableWrite() {
    isWriteLog = false;
}

void ProxyLogger::switchWriteMode() {
    isWriteInFile = !isWriteInFile;
    isWriteInTerminal =! isWriteInTerminal;
}
