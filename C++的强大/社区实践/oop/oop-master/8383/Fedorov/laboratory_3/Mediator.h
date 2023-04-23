#ifndef MEDIATOR_H
#define MEDIATOR_H

class Unit;
class GameField;

class IMediator
{
public:
    virtual bool notify(Unit* unit, int x, int y) = 0;
    virtual ~IMediator();
};


class AttackMediator : public IMediator
{
protected:
    GameField* field;
    int getDistant(int x1, int y1, int x2, int y2);
public:
    virtual bool notify(Unit* unit, int x, int y) override;
    AttackMediator(GameField*);
    virtual ~AttackMediator();
};



#endif // MEDIATOR_H
