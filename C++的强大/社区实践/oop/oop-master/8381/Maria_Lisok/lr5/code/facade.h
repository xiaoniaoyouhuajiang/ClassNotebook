#ifndef FACADE_H
#define FACADE_H
#include "ui_mainwindow.h"

#include "command/gamecommand.h"

#include "logger/adapter.h"

#include "logger/proxylogger.h"
class Facade
{
public:
    Facade(Ui::MainWindow *ui, Game *game);
    string getGameInfo();
    string getBaseInfo(int number);
    string getUnitInfo(int x, int y);
    string getNeutralInfo(int x, int y);
    string getLandscapeInfo(int x, int y);
    void moveUnit(int x, int y, int xDelta, int yDelta);
    void attackUnit(int x, int y, int xDelta, int yDelta);
    void addBase(int x, int y, int, int);
    void addUnit(int base, int type);
    void addNeutral(int x, int y, int type);
    Adapter *getLogger() const;
    void setLogger(LogPlace logPlace);
    void saveGame(string name);
    void loadGame(string name);
    ~Facade();

private:
    Ui::MainWindow *ui;
    Game *game;
    Adapter* logger;
};

#endif // FACADE_H
