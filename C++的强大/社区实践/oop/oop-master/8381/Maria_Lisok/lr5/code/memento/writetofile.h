#ifndef WRITETOFILE_H
#define WRITETOFILE_H
#include "gameparam.h"
#include <fstream>
class WriteToFile
{
public:
    WriteToFile(string name);
    ~WriteToFile();
    void write(GameParam* params);
private:
    ofstream file;
    string nameFile;
};

#endif // WRITETOFILE_H
