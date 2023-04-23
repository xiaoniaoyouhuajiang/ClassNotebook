#ifndef OOP_FILE_H
#define OOP_FILE_H

#include <iostream>
#include <fstream>
#include <sstream>

/*
 * File -- класс для записи файл по идиоме RAII.
 */

class File
{
public:
    File(const std::string& fileName, std::string mode);
    ~File();

    void writeString(const std::string str);
    std::stringstream readString();

private:
    std::fstream file;
    bool isFileOpen;
};


#endif //OOP_FILE_H
