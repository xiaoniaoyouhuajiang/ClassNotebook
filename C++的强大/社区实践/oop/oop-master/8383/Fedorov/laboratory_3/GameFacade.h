#ifndef GAMEFACADE_H
#define GAMEFACADE_H

class GameField;
class BaseConstructor;
class Game;

class GameFacade
{
GameField* field;
Game* game;
BaseConstructor* baseConstructor;
int buffX, buffY;
public:
    bool createBase(int x, int y);
    bool clicked(int x, int y);
    GameFacade(GameField*, Game*, BaseConstructor*);
    virtual ~GameFacade();
};

#endif // GAMEFACADE_H
