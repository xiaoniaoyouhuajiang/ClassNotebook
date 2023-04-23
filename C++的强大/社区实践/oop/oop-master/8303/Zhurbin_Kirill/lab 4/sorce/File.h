#ifndef OOP1_FILE_H
#define OOP1_FILE_H

#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>

class FileWrite {
    std::ofstream out;
public:
    FileWrite (const std::string& filename, std::string mod)  {
        if (mod == "log")
            out.open(filename, std::ios::app | std::ios::out);
        else
            out.open(filename);
    }

    ~FileWrite() {
        out.close();
    }

    
    void write(std::string data) {
        out << data << std::endl;
    }

};

class FileRead {
    std::ifstream in;
public:
    FileRead (std::string filename)  {
        in.open(filename);
    }

    ~FileRead() {
        in.close();
    }

    std::stringstream read() {
        std::string s;
        std::stringstream strStream;
        strStream << in.rdbuf();
        return strStream;
    }

};

#endif //OOP1_FILE_H