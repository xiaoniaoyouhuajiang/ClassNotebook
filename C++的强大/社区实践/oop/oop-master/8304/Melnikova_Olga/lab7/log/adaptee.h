#ifndef ADAPTEE_H
#define ADAPTEE_H
#pragma once
#include "iostream"
#include "ostream"
#include "fstream"
#include "QFile"

class Adaptee
{
public:
    std::ofstream out;
    Adaptee(){
        out.open("./log.txt",  std::ios_base::out | std::ios_base::app);
    }
    ~Adaptee(){
        out.close();
    }

    friend std::ostream& operator << (std::ostream& out, std::string str){
        out << str << std::endl;
        return out;
    }

    bool WriteToFile(std::string str){
        if (out.is_open())
        {
            out << str << std::endl;
        }
        return true;
    }
    bool WriteToTerminal(std::string str){
        std::cout << str <<std::endl;
        return true;
    }
};

#endif // ADAPTEE_H
