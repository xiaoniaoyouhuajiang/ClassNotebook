#ifndef LABOOP_GAMEFIELD_HPP
#define LABOOP_GAMEFIELD_HPP

#include "objects/Base.hpp"

#define MAX_UNITS 10

class GameField {
public:
    explicit GameField(int width=10, int height=10);
    ~GameField() {};
    GameField(const GameField &field);
    GameField& operator=(const GameField& field);
    void setSize(int w, int h) {width = w; height = h;};
    int getWidth() { return width;};
    int getHeight() {return height;};
    void createUnit(UnitName unitName, int x, int y);
    void deleteUnit(int x, int y);
    void moveUnit(int x1, int y1, int x2, int y2);
    FieldCell *getCell(int x, int y) {return &gameField[x][y];};
    void setBase(int x, int y);
    Base *getBase() {return base;};
    void attackUnit(int x1, int y1, int x2, int y2);
    void makeActionWithObj(int x, int y);
private:
    int width;
    int height;
    FieldCell **gameField;
    Base *base;
    int numUnits;
};


#endif //LABOOP_GAMEFIELD_HPP
