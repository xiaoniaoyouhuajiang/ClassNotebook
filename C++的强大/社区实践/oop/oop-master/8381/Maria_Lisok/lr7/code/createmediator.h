#ifndef CREATEMEDIATOR_H
#define CREATEMEDIATOR_H

class PlayingField;
class Base;
class Unit;
class CreateMediator
{
private:
    Base* base;
    PlayingField* field;
public:
    CreateMediator(PlayingField* field, Base *base);
    void notify(Unit * item, unsigned x, unsigned y);
};

#endif // CREATEMEDIATOR_H
