#include <sstream>
#include "Adapter.h"
#include "Unit.h"
#include "Field.h"


Adapter::Adapter(bool writeAble, bool fileWriteAble): writeAble(writeAble), fileWriteAble(fileWriteAble){

}

std::ostream& operator<< (std::ostream &out, const Unit& unit)
{
    out << unit.name << ",  health: " << unit.condition.health << ",  attack: " << unit.condition.attack << ", armor: " << unit.condition.armor;
    return out;
}

std::ostream& operator<< (std::ostream &out, const Base& base)
{
    out << base.numberBase << ",  x: " << base.BaseX << ",  y: " << base.BaseY << ", health: " << base.health << ", max count unit: " << base.maxCountUnit;
    return out;
}

std::ostream& operator<< (std::ostream &out, const Field& field)
{
    out << "  x: " << field.lenghtX << ",  y: " << field.lengthY <<  ", max count unit: " << field.maxCountObject;
    return out;
}

void Adapter::unitDeath(char name){
     print("Unit " + std::string(1, name) + " has been killed", writeAble, fileWriteAble);
}

void Adapter::createUnit(Unit* unit){
    std::ostringstream status;
    status << "Create unit  " << *unit;
    print(status.str() , writeAble, fileWriteAble);
}



void Adapter::attackBase(int numberBase){
    print("Base #" + std::to_string(numberBase) + " was attacked", writeAble, fileWriteAble);
}

void Adapter::unitAttacked(char name){
    print("Unit " + std::string(1, name) + " has been attacked", writeAble, fileWriteAble);
}

void Adapter::createField(Field* field){
    std::ostringstream status;
    status << "Create field" << *field;
    print(status.str(), writeAble, fileWriteAble);
}

void Adapter::moveUnit(char name, int x, int y){
    print("Unit " + std::string(1, name) + " moved to x = " + std::to_string(x) + " , y = " +  std::to_string(y), writeAble, fileWriteAble);
}

void Adapter::unitAttackBase(char name, int numberBase){
    print("Unit " + std::string(1, name) + " attacked base #" + std::to_string(numberBase), writeAble, fileWriteAble);
}

void Adapter::unitAttackUnit(char name1, char name2){
    print("Unit " + std::string(1, name1) + " attacked unit " + std::string(1, name2), writeAble, fileWriteAble);
}

void Adapter::createBase(Base* base){
    std::ostringstream status;
    status << "Create base#" << *base;
    print(status.str(), writeAble, fileWriteAble);
}

void Adapter::switchLog(std::string mod){
    print("Swith logger mode to " + mod, writeAble, fileWriteAble);
}

void Adapter::incorrectFile(){
    print("Load file incorrect, loadding stopped", writeAble, fileWriteAble);
}

void Adapter::gameSaved(){
    print("Game saved", writeAble, fileWriteAble);
}

void Adapter::gameLoaded(){
    print("Game loaded", writeAble, fileWriteAble);
}


