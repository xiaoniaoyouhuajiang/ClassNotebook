#ifndef OOP1_GAMEBOARD_H
#define OOP1_GAMEBOARD_H

#include "Cell.h"

class Board{
    friend Building;
private:
    int width;
    int height;
    int objectOnBoard;
    int coin;
    Cell*** cells;
public:
    Board(int w, int h);
    Board(const Board& old);
    Board(Board&& before);
    ~Board() = default;
    int getWidth();
    int getHeight();
    void newBuild();
    void delBuild();
    void info();
};

#endif //OOP1_GAMEBOARD_H
