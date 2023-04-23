#ifndef FACADE_H
#define FACADE_H
#include "ui_mainwindow.h"

#include "game/game.h"
#include "command/gamecommand.h"

class Facade
{
public:
    Facade(Ui::MainWindow *ui, Game *game);
    void getGameInfo();
    void getBaseInfo(int number);
    void getUnitInfo(int x, int y);
    void getNeutralInfo(int x, int y);
    void getLandscapeInfo(int x, int y);
    void moveUnit(int x, int y, int xDelta, int yDelta);
    void attackUnit(int x, int y, int xDelta, int yDelta);
    void addBase(int x, int y, int, int);
    void addUnit(int base, int type);
    void addNeutral(int x, int y, int type);

private:
    Ui::MainWindow *ui;
    Game *game;
};

#endif // FACADE_H
