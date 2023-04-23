#include "SnapshotField.h"
#include <sstream>
#include "Field.h"
#include "File.h"
#include "Mediator.h"
#include "Exceptions.h"

SnapshotField::SnapshotField(Field* field, int lengthX, int lengthY, int maxCountObject, int countUnit, Base* base1, Base* base2): field(field), lenghtX(lengthX), lengthY(lengthY), maxCountObject(maxCountObject), countUnit(countUnit), mapCell(mapCell), base1(base1), base2(base2){
    fileWrite = new FileWrite("saveField.txt", "save");
}

SnapshotField::SnapshotField(Field* field): field(field){
    fileRead = new FileRead("saveField.txt");
}

SnapshotField::~SnapshotField() {
    delete fileWrite;
    delete fileRead;
}

void SnapshotField::save(){
    std::ostringstream out;
    this->adapter = field->getAdapter();

    out << lenghtX << " " << lengthY << " " << maxCountObject  << std::endl;

    if (field->base1 == nullptr){
        out << "no" << std::endl;
        fileWrite->write(out.str());
        adapter->gameSaved();
        return;
    }

    else
        out << "yes" << std::endl;

    out << base1->BaseX << " ";
    out << base1->BaseY << " ";
    out << base1->maxCountUnit << " ";
    out << base1->health << " ";
    out << base1->countUnit << " ";
    out << base1->numberBase << " " << std::endl;


    Unit* unit;
    for (int i = 0; i < field->base1->countUnit; i++){
        unit = base1->getUnit();
        out << unit->name << " " << unit->condition.health << " " << unit->condition.attack << " " << unit->condition.armor << " " << field->findUnit(unit)->x << " " << field->findUnit(unit)->y << std::endl;
    }

    if (field->base2 == nullptr){
        out << "no" << std::endl;
        fileWrite->write(out.str());
        adapter->gameSaved();
        return;
    }

    else
        out << "yes" << std::endl;

    out << base2->BaseX << " ";
    out << base2->BaseY << " ";
    out << base2->maxCountUnit << " ";
    out << base2->health << " ";
    out << base2->countUnit << " ";
    out << base2->numberBase << std::endl;

    for (int i = 0; i < field->base2->countUnit; i++){
        unit = base2->getUnit();
        out << unit->name << " " << unit->condition.health << " " << unit->condition.attack << " " << unit->condition.armor << " " << field->findUnit(unit)->x << " " << field->findUnit(unit)->y << std::endl;
    }

    fileWrite->write(out.str());
    adapter->gameSaved();
}

void SnapshotField::load(Mediator* mediator){

    std::stringstream stream = fileRead->read();

    int fieldX, fieldY, maxCountUnit;
    adapter = new Adapter();


    stream >> fieldX >> fieldY >> maxCountUnit;
    if (stream.fail())
        throw TypeInputException("int");

    if (fieldX != 10 && fieldX != 8)
        throw LogicException("field coordinates", fieldX);
    if (fieldY != 10 && fieldY != 8)
        throw LogicException("field coordinates", fieldY);
    if (maxCountUnit <= 0)
        throw LogicException("max count of field unit", maxCountUnit);


    Field*  newField = new Field(fieldX, fieldY, maxCountUnit, adapter);
    *(this->field) = *newField;
    field->addLandscape();
    mediator->setField(field);

    std::string flagContain;

    stream >> flagContain;

    if (flagContain != "yes" && flagContain != "no"){
        throw LogicException("flag of base", flagContain);
    }

    if (flagContain == "no") {
        adapter->gameLoaded();
        return;
    }

    int baseX, baseY, maxCountUnitBase, health, countUnitBase, numberBase;

    stream >> baseX >> baseY >> maxCountUnitBase >> health >> countUnitBase >> numberBase;
     if (stream.fail())
        throw TypeInputException("int");

    if (baseX < 0)
        throw LogicException("base coordinates", baseX);
    if (baseY < 0)
        throw LogicException("base coordinates", baseY);
    if (maxCountUnitBase <= 0)
        throw LogicException("max count unit of base", maxCountUnit);
    if (health < 0)
        throw LogicException("health of base", health);
    if (numberBase != 1 && numberBase != 2 && numberBase != 3)
        throw LogicException("number base", numberBase);

    field->createBase(baseX, baseY, maxCountUnitBase, health, adapter);

    char name;
    int healthUnit, attack, armor, x, y;

    for (int i=0; i<countUnitBase; i++){

        stream >> name;
        if (stream.fail()){
            throw TypeInputException("char");
        }

        stream >> healthUnit >> attack >> armor >> x >> y;
        if (stream.fail())
            throw TypeInputException("int");

        if (healthUnit <= 0)
            throw LogicException("health of unit", healthUnit);
        if (attack <= 0)
            throw LogicException("attack of unit", attack);
        if (armor <= 0)
            throw LogicException("armor of unit", armor);
        if (x < 0)
            throw LogicException("coordinate x of unit", x);
        if (y < 0)
            throw LogicException("coordinate y of unit", y);

        field->base1->setUnit(name, x, y, healthUnit, attack, armor,  mediator, adapter);
    }

    stream >> flagContain;

    if (flagContain != "yes" && flagContain != "no"){
        throw LogicException("flag of base", flagContain);
    }

    if (flagContain == "no") {
        adapter->gameLoaded();
        return;
    }

    stream >> baseX >> baseY >> maxCountUnitBase >> health >> countUnitBase >> numberBase;
    if (stream.fail())
        throw TypeInputException("int");

    if (baseX < 0)
        throw LogicException("base coordinates", baseX);
    if (baseY < 0)
        throw LogicException("base coordinates", baseY);
    if (maxCountUnitBase <= 0)
        throw LogicException("max count unit of base", maxCountUnit);
    if (health < 0)
        throw LogicException("health of base", health);
    if (numberBase != 1 && numberBase != 2 && numberBase != 3)
        throw LogicException("number base", numberBase);

    field->createBase(baseX, baseY, maxCountUnitBase, health, adapter);

    for (int i=0; i<countUnitBase; i++){

        stream >> name;
        if (stream.fail())
            throw TypeInputException("char");

        stream >> healthUnit >> attack >> armor >> x >> y;
        if (stream.fail())
            throw TypeInputException("int");

        if (healthUnit <= 0)
            throw LogicException("health of unit", healthUnit);
        if (attack <= 0)
            throw LogicException("attack of unit", attack);
        if (armor <= 0)
            throw LogicException("armor of unit", armor);
        if (x < 0)
            throw LogicException("coordinate x of unit", x);
        if (y < 0)
            throw LogicException("coordinate y of unit", y);

        field->base2->setUnit(name, x, y, healthUnit, attack, armor, mediator, adapter);
    }

    adapter->gameLoaded();
}


