#ifndef OOP_WORLD_H
#define OOP_WORLD_H
#include <random>
#include <iostream>
#include <fstream>
#include <ctime>
#include "AbstractObject.h"
#include "Unit.h"

class ClosedCells : public AbstractObject {
public:
    ClosedCells(char pict);
};

class Tree : public ClosedCells {
public:
    Tree();
};

class Rock : public ClosedCells {
public:
    Rock();
};

class Wall : public ClosedCells {
public:
    Wall();
};

class Road : public AbstractObject {
public:
    Road(char pict = '_');
};

class Cell {
protected:
    bool isUnit = false;
    bool isWall = false;
    bool isLoot = false;
    AbstractObject *object;
public:
    explicit Cell(bool isUnit = false, bool isWall = false);
    char getLoot();
    bool getIsLoot() const;
    Unit *getUnit() const;
    bool getIsWall() const;
    bool getIsUnit() const;
    bool isEmpty() const;
    template<class ClosedCellsClass>
    Cell &setWall();
    template<class UnitClass>
    Cell &setUnit();
    template<class NeutralClass>
    Cell &setNeutral();
    Cell &setPlayer(char playerName);
    Cell &delWall();
    Cell &delUnit();
    Cell &setBase(std::vector<Unit*> units, int unitCount, int maxUnit);
    Base *getBase();
    Cell &operator=(Cell &from);
    friend std::ostream &operator<<(std::ostream &out, const Cell &cc);
};

class World {
    int height = 10;
    int width = 10;
protected:
    Cell **cells;
public:
    explicit World(int h, int w, int maxObj, int maxUnit);
    explicit World(std::ifstream &file);
    World(const World &w);
    void dropLoot();
    World &operator=(const World &w);
    int getHeight() const;
    int getWidth() const;
    Cell &getCell(int x, int y);
    Cell &getCell(std::pair<int, int>coord);
    void switchUnit(int x, int y, int choose());
    void setBase(std::vector<Unit*> units, int unitCount, int maxUnit);
    void assistBase(Base& b);
    ~World();
};

#endif //OOP_WORLD_H