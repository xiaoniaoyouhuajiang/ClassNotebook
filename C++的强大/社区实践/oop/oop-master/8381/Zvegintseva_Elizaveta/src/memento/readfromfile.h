#ifndef READFROMFILE_H
#define READFROMFILE_H

#include "gameparam.h"
#include <fstream>
class ReadFromFile
{
public:
    ReadFromFile(string name);
    ~ReadFromFile();
    GameParam* read();
private:
    ifstream file;
    string nameFile;
};

#endif // READFROMFILE_H
