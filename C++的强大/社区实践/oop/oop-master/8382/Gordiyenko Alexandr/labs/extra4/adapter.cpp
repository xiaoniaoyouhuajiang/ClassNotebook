#include "adapter.h"
#include <sstream>
#include "../Units/Unit.h"
#include "../Field.h"
#include "../Base.h"

Adapter::Adapter(bool consoleWrite, bool fileWrite): consoleWrite(consoleWrite), fileWrite(fileWrite){}

std::ostream& operator<< (std::ostream &out, const Field& field) {
    out << "  x: " << field.x << ",  y: " << field.y <<", count unit: "
        << field.curUnit << ", max count unit: " << field.maxUnit ;
    return out;
}

std::ostream& operator<< (std::ostream &out, Base& base) {
    out << "  x: " << base.x << ",  y: " << base.y <<  ", count unit: " << base.countUnit
        << ", max count unit: " << base.maxCountUnit;
    return out;
}

std::ostream& operator<< (std::ostream &out, Unit& unit) {
    out << "  x: " << unit.x << ",  y: " << unit.y << "type: " << unit.type();
    return out;
}


void Adapter::createField(Field* field) {
    std::ostringstream status;
    status << "Create field" << *field;
    print(status.str(), consoleWrite, fileWrite);
}

void Adapter::createBase(Base* base) {
    std::ostringstream status;
    status << "Create base#" << *base;
    print(status.str(), consoleWrite, fileWrite);
}

void Adapter::createUnit(Unit *unit) {
    std::ostringstream status;
    status << "Create unit" << *unit;
    print(status.str(), consoleWrite, fileWrite);
}

// consoleWrite , fileWrite;
void Adapter::moveUnit(Unit *unit) {
    std::ostringstream status;
    status << "Move unit" << *unit;
    print(status.str(), consoleWrite, fileWrite);

}

void Adapter::switchLog(std::string mod){

    print("Swith logger mode to " + mod, consoleWrite, fileWrite);

    if(mod=="fileOn")
        fileWrite = true;
    if(mod=="consoleOn") {
        if(!consoleWrite)
            print("Swith logger mode to " + mod, 1, fileWrite);
        consoleWrite = true;
    }
    if(mod=="fileOff")
        fileWrite = false;
    if(mod=="consoleOff")
        consoleWrite = false;
}

void Adapter::gameSaved()
{
    print("Game saved", consoleWrite, fileWrite);
}

void Adapter::gameLoaded()
{
    print("Game loaded", consoleWrite, fileWrite);
}