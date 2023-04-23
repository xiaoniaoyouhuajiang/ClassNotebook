#pragma once
#include <iostream>
#include <fstream>

class File {
public:
    std::fstream file;
    File(const std::string& fileName);
    File(const std::string& fileName, bool flag);
    ~File();
    void write(std::string& message);
    std::string read(std::string& message);
    bool isOpen();
};