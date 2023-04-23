#ifndef PROXY_H
#define PROXY_H
#pragma once
#include "adaptee.h"
#include "iostream"

class Proxy
{
public:
    Proxy(Adaptee* write, bool logToFile, bool logToTerminal, bool withoutLog){
        this->write = write;
        this->logToFile = logToFile;
        this->logToTerminal = logToTerminal;
        this->withoutLog = withoutLog;
    }

    Adaptee* write;
    bool logToFile;
    bool logToTerminal;
    bool withoutLog;

    bool SpecificRequest(std::string str){
        if(withoutLog){

        }else{
            if(logToFile){
                this->write->WriteToFile(str);
            }
            if(logToTerminal){
                this->write->WriteToTerminal(str);
            }
        }
        return true;
    }
};

#endif // PROXY_H
