#ifndef FILEIN_H
#define FILEIN_H

#include <iostream>
#include <string>
#include <fstream>

class FileIn {

    std::FILE* file;

public:
    FileIn(const char* filename) : file(std::fopen(filename, "r"))
    {
        if (!file){
            throw std::runtime_error("file open failure");
        }
    }
    ~FileIn()
    {
        std::fclose(file);
    }

    std::string read()
    {
        char str[1000] = "";
        std::ifstream ifs ("Game field dump.txt", std::ios_base::binary);
        if (ifs.is_open ())
        {
             ifs.seekg (0, std::ios::end);
             int size = ifs.tellg ();
             ifs.seekg (0, std::ios::beg);

             if (size == 0){
                std::cout << "Load file is empty!\n";
                ifs.close();
                return "";
             }
             ifs.close();
        }
        if (fgets(str, 1000, file) == NULL){
            ;
        }

        std::string res(str);
        return res;
    }
};

#endif // FILEIN_H
