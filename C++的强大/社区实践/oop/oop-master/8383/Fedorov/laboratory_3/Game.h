#ifndef GAME_H
#define GAME_H
#include "Event.h"
#include <string>

class GameField;
class BaseConstructor;
class GameFacade;

class Game{
  private:
    int width = 40;
    int hight = 40;
    int xWin;
    int yWin;
    bool unitActive;
    bool baseActive;
    bool infoActive;
    void initWindow();
    void initCurses();
    GameField* field;
    BaseConstructor* baseConstructor;
    GameFacade* facade;
    std::string message;
  public:
    bool getUnitActive();   /* вынести в класс атрибут */
    bool getBaseActive();
    bool getInfoActive();
    void setInactive();
    void setUnitActive(bool);
    void setBaseActive(bool);
    void setInfoMessage(Event);
    void run();
    Game();
    virtual ~Game();

};
#endif // GAME_H
