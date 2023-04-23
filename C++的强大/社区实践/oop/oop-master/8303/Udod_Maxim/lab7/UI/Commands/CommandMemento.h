//
// Created by shenk on 02.04.2020.
//

#ifndef UNTITLED13_COMMANDMEMENTO_H
#define UNTITLED13_COMMANDMEMENTO_H


#include <string>
#include <fstream>
#include <utility>

class CommandMemento{

private:

    std::string commandLine;

public:

    CommandMemento(std::string commandLine): commandLine(std::move(commandLine)){}
    void saveToFile(std::ofstream &fs) const{

        fs << commandLine;

    }

    unsigned long int getHash(std::hash<std::string> &hashFunc){

        return hashFunc(commandLine);

    }

};


#endif //UNTITLED13_COMMANDMEMENTO_H
