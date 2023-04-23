//
// Created by Artem Butko on 21.05.2020.
//

#ifndef OOP_NEW_FILE_H
#define OOP_NEW_FILE_H

#include <iostream>

/*
 * File -- класс для создания файла по идиоме RAII.
 */

class File
{
public:
    File(const char* fileName);
    ~File();

    void writeString(const char* string);
    bool isOpen();

private:
    std::FILE* file;
    bool isFileOpen;
};


#endif //OOP_NEW_FILE_H
