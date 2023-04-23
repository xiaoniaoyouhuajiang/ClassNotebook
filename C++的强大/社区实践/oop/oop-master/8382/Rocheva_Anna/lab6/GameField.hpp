#ifndef LABOOP_GAMEFIELD_HPP
#define LABOOP_GAMEFIELD_HPP

#include "objects/Base.hpp"

#define MAX_UNITS 10


class GameField {
public:
    explicit GameField(int width=20, int height=20);
    ~GameField() {};
    GameField(const GameField &field);
    GameField& operator=(const GameField& field);
    void setSize(int w, int h) {width = w; height = h;};
    int getWidth() { return width;};
    int getHeight() {return height;};
    void createUnit(UnitName unitName, int x, int y, Base *base);
    void deleteUnit(int x, int y, Base *base);
    void moveUnit(int x1, int y1, int x2, int y2, Base *base);
    FieldCell *getCell(int x, int y) {return &gameField[x][y];};
    void setBase(int x, int y);
    void attackUnit(int x1, int y1, int x2, int y2, Base *base, Base *enemyBase);
    void attackBase(int x1, int y1, int x2, int y2, Base *base, Base *enemyBase);
    void makeActionWithObj(int x, int y);
    std::string getLogString() {return logString;};
    int getNumUnits() { return numUnits;};
private:
    int width;
    int height;
    FieldCell **gameField;
    int numUnits;
    std::string logString;
};

class Iterator {
public:
    explicit Iterator(GameField *gameField) : gameField(gameField) {x = 0; y = 0; current = gameField->getCell(0, 0);};
    FieldCell *First() {return gameField->getCell(0, 0);};
    void Next() {
        if (gameField->getWidth() % x == 1){
            x = 0;
            y++;
            if (y == gameField->getHeight())
                y = 0;
        } else {
            x++;
        }
    };
    bool IsDone() {
        return x == gameField->getWidth() && y == gameField->getHeight();
    };
    FieldCell *Current() { return gameField->getCell(x, y);};

private:
    GameField *gameField;
    FieldCell *current;
    int x, y;
};


#endif //LABOOP_GAMEFIELD_HPP
