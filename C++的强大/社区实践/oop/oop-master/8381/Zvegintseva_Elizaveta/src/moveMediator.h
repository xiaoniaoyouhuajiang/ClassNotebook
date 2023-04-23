#ifndef MOVEMEDIATOR_H
#define MOVEMEDIATOR_H

class PlayingField;
class Unit;
class IUnit;

class MoveMediator{
public:
    MoveMediator(PlayingField*, Unit*);
    void moveObj(Unit* item, int x, int y);
    ~MoveMediator()=default;
private:
    PlayingField* playingField;
    Unit* playingFieldItem;
};

#endif // MOVEMEDIATOR_H
