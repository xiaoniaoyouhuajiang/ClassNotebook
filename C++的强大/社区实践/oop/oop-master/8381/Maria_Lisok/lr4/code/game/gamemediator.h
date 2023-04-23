#ifndef GAMEMEDIATOR_H
#define GAMEMEDIATOR_H

class Game;
class Unit;
class Base;

class GameMediator
{
public:
    GameMediator(Game* game, Base* base);
    void Notify(Unit* u, bool add);
    ~GameMediator() = default;
private:
    Game* game;
    Base* base;
};

#endif // GAMEMEDIATOR_H
