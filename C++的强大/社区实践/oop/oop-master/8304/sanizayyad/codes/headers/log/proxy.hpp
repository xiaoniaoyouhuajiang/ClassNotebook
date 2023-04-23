#ifndef proxy_hpp
#define proxy_hpp

#include <stdio.h>
#include <iostream>
#include "terminallog.hpp"
#include "filelog.hpp"
#include "unitlog.hpp"
#include "playerlog.hpp"



class Proxy
{
public:
    Proxy(bool logToFile,bool logToTerminal){
        this->logToFile = logToFile;
        this->logToTerminal = logToTerminal;
        this->path = "/Users/sourcecode/Documents/LabFolder/log.txt";
    }

    bool logToFile;
    bool logToTerminal;

    void logMessage(std::string message, TYPE type = TYPE::INFO){
        if(logToFile){
            log = std::make_shared<FileLog>(path);
            log->writeTo(message,type);
        }
        if(logToTerminal){
            log = std::make_shared<TerminalLog>();
            log->writeTo(message,type);
        }
    }
private:
    std::shared_ptr<Adapter> log;
    std::string path ;

};
#endif /* proxy_hpp */
