#ifndef LABS_RAII_H
#define LABS_RAII_H

#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>

class RAII { // RAII
    std::ofstream out;
public:
    RAII(const std::string &filename, std::string opt){
        out.open(filename);
    }
    ~RAII(){
        out.close();
    }
    void write(std::string data) {
        out << data;
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
#endif //LABS_RAII_H
