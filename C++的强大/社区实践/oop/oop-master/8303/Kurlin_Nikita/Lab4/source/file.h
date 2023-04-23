#ifndef FILE_H
#define FILE_H

#include <iostream>

class File {

    std::FILE* file;

public:
    File(const char* filename) : file(std::fopen(filename, "w+"))
    {
        if (!file)
            throw std::runtime_error("file open failure") ;
    }
    ~File()
    {
        std::fclose(file);
    }

    void write(const char* str)
    {
        if (std::fputs(str, file) == EOF)
            throw std::runtime_error("file write failure") ;
    }
};

#endif // FILE_H
