#include "gamememento.h"

GameMemento::GameMemento(string name, GameParam* params): nameFile(name), params(params)
{
    WriteToFile in(nameFile);
    in.write(params);
}

GameMemento::GameMemento(string name): nameFile(name), params(nullptr)
{}

GameParam* GameMemento::loadFromFile()
{
    ReadFromFile out(nameFile);
    return out.read();
}
