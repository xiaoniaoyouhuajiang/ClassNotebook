#ifndef OOP1_CELL_H
#define OOP1_CELL_H

#include "IUnit.h"

class Cell{
private:
    IUnit* buildingOnCell;
public:
    Cell();
    Cell(const Cell& oldCell);
    void addBuild(char type);
    void aboutCell();
    int aboutCell_Saldo();
    void removeBuild();
    char typeBuild();
};

class FactoryOfBuildings{
public:
    Building* creator(TypeOfBuild typeOfB);
};

#endif //OOP1_CELL_H
