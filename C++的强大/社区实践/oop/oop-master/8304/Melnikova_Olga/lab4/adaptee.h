#ifndef ADAPTEE_H
#define ADAPTEE_H
#pragma once
#include "iostream"
#include "fstream"
#include "QFile"

class Adaptee
{
public:
    Adaptee(){}

    bool WriteToFile(std::string str){
        std::ofstream out;
        out.open("./log.txt",  std::ios_base::out | std::ios_base::app);
        if (out.is_open())
        {
            out << str << std::endl;
            out.close();
        }
        return true;
    }
    bool WriteToTerminal(std::string str){
        std::cout<<str<<std::endl;
        return true;
    }
};

#endif // ADAPTEE_H
