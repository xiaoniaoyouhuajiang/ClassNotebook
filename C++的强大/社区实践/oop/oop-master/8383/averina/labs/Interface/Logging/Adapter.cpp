
#include "Adapter.h"

std::ostream& operator<<(std::ostream& out, const Object& object)
{
    out << " id = " << object.id;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Base& base)
{
    out << " x = " << base.x << ", y = " << base.y << ", id = " << base.id << ", unit limit = " << base.unitLimit;
    return out;
}

std::ostream& operator<<(std::ostream& out, const Field& field)
{
    out << " height = " << field.height << ", width = " << field.width << ", object limit = " << field.objLimit;
    return out;
}

std::string Adapter::createBase(Base* base)
{
    std::ostringstream outstring;
    outstring << "<log>: base was created: " << *base;
    return outstring.str();
}

std::string Adapter::createUnit(char id)
{
    std::ostringstream outstring;
    outstring << "<log>: unit was created: " << id;
    return outstring.str();
}

std::string Adapter::getUnit(Object *unit, int x, int y)
{
    std::ostringstream outstring;
    outstring << "<log>: unit getting on field: " << *unit << ", on x = " << x << ", on y = " << y;
    return outstring.str();
}

std::string Adapter::moveUnit(Object *unit, int x, int y, int i, int j)
{
    std::ostringstream outstring;
    outstring << "<log>: unit moving: " << *unit << ", from x = " << x << ", y = " << y << ", to x = " << i << ", y = " << j;
    return outstring.str();
}

std::string Adapter::attackUnit(Object *unit, int x, int y, int i, int j)
{
    std::ostringstream outstring;
    outstring << "<log>: unit attack: " << *unit << ", damage = " << unit->damage.getDamage() << ", from x = " << x << ", y = " << y << ", to x = " << i << ", y = " << j;
    return outstring.str();
}