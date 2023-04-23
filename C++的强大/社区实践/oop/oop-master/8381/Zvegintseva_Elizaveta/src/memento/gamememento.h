#ifndef GAMEMEMETO_H
#define GAMEMEMETO_H

#include "memento.h"
#include "readfromfile.h"
#include "writetofile.h"
class GameMemento : public Memento
{
public:
    GameMemento(string name, GameParam* params);
    GameMemento(string name);
    GameParam* loadFromFile();
private:
    string nameFile;
    GameParam* params;
};

#endif // GAMEMEMETO_H
