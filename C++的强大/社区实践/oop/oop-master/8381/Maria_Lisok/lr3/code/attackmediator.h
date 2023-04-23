#ifndef ATTACKMEDIATOR_H
#define ATTACKMEDIATOR_H

#include <vector>

class Unit;
class PlayingField;

class AttackMediator
{
public:
    AttackMediator(PlayingField* field);
    void addUnit(Unit* u);
    void deleteUnit(Unit* u);
    void attack(Unit* u, int x, int y);
    std::vector<Unit *> getUnits() const;
private:
    std::vector<Unit*> units;
    PlayingField* field;
};

#endif // ATTACKMEDIATOR_H
