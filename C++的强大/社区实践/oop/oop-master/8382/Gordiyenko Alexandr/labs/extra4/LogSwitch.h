#ifndef LABS_LOGSWITCH_H
#define LABS_LOGSWITCH_H

#include <string>
#include <iostream>
#include "../extra5/RAII.h"

class LogSwitch{

protected:
    void printConsole(std::string message){
        std::cout<<"<log: >"<<message<<std::endl;
    }

    void printFile(std::string message){
        RAII file("Logs.txt", "log");
        file.write("<log:> " + message);
    }

};

#endif //LABS_LOGSWITCH_H
