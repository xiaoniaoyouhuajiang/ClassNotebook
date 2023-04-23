#include "adapter.h"
#include "base.h"
#include "gamefield.h"

using namespace std;

Adapter::Adapter()
{

}

ostream& operator<< (ostream& out, const Base& base)
{
    return out << "Base: " << base.baseNumb << ". Max unit count, health, coordinates = " << base.maxCount << ", " << base.health <<
                  ", (" << base.x << ";" << base.y << ")";
}

ostream& operator<< (ostream& out, const Unit& unit)
{
    return out << unit.name << ". Health, armor, attack = " << unit.attributes->health << ", " << unit.attributes->armor <<
                  ", " << unit.attributes->attack;
}

ostream& operator<< (ostream& out, const GameField& field)
{
    return out << "Max unit count, size (length*height) = " << field.maxCount << ", (" << field.x << ";" << field.y << ")";
}

string Adapter::unitCreation(Unit* unit, int x, int y, int baseNumb)
{
    ostringstream out("");
    out << "[Unit creation " << *unit << ", (" << x << ";" << y << ") Base: " << baseNumb << "]\n";
    return out.str();
}

string Adapter::unitMoving(Unit* unit, int xx, int yy, int baseNumb)
{
    return "[Unit moving (" + unit->getName() + ") to (" + to_string(xx) + ";" + to_string(yy) + ") Base: " + to_string(baseNumb) + "]\n";
}

string Adapter::baseCreation(Base* base)
{
    ostringstream out("");
    out << "[Base creation. " << *base << "]\n";
    return out.str();
}

string Adapter::fieldCreation(GameField* field)
{
    ostringstream out("");
    out << "[Game Field creation. " << *field << "]\n";
    return out.str();
}

string Adapter::unitDeletion(Unit* unit, int x, int y)
{
    return "[Unit killed (" + unit->getName() + ")" + " (" + to_string(x) + ";" + to_string(y) + ")]\n";
}

string Adapter::baseDestruction(Base* base)
{
    ostringstream out("");
    out << "[Base was destroyed. " << *base << "]\n";
    return out.str();
}

string Adapter::baseDamage(Base* base)
{
    ostringstream out("");
    out << "[Base was damaged. " << *base << "]\n";
    return out.str();
}

string Adapter::unitDamage(Unit* unit, int xx, int yy)
{
    return "[Unit was damaged (" + unit->getName() + ")" + " (" + to_string(xx) + ";" +
            to_string(yy) + ") Health = " + to_string(unit->getHealth()) + "]\n";
}
