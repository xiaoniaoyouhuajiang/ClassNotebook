#ifndef CELL_H
#define CELL_H
#include "unit.h"
#include "NeutralObj/neutralObj.h"
#include "Landscape/landscape.h"
#include "Landscape/forest.h"
#include "Landscape/mountain.h"
#include "Landscape/river.h"
#include "Base/base.h"

class Cell{
public:
    Cell();
    ~Cell();
    Cell(const Cell& cell);
    Cell(Cell&& cell);
    Cell& operator= (const Cell& cell);
    Cell& operator= (Cell&& cell);
    void addUnit(Unit* unit);
    void delUnit();
    void addNeutral(NeutralObj*);
    void delNeutral();
    bool isUnitFree() const;
    Unit* getUnit() const;
    NeutralObj* getNeutral() const;
    string characteristic(unsigned, unsigned);
    Landscape *getLandscape() const;
    void setLandscape(Landscape *value);
    Base *getBase() const;
    void setBase(Base *value);

private:
    Unit* unit{};
    NeutralObj* neutral{};
    Landscape* landscape{};
    Base* base{};
};
#endif // CELL_H
