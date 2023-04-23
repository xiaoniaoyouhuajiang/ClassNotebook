#ifndef MEDIATOR_H
#define MEDIATOR_H


class GameField;


class Unit;


class Mediator
{
public:
    Mediator(GameField* field);

    bool notify(Unit* unit, int x, int y);

private:
    GameField* field;
};

#endif // MEDIATOR_H
