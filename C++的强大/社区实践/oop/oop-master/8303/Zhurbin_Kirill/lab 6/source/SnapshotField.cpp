#include "SnapshotField.h"
#include <sstream>
#include "Field.h"
#include "File.h"
#include "Mediator.h"

SnapshotField::SnapshotField(Field* field, int lengthX, int lengthY, int maxCountObject, int countUnit, Base* base1, Base* base2): field(field), lenghtX(lengthX), lengthY(lengthY), maxCountObject(maxCountObject), countUnit(countUnit), mapCell(mapCell), base1(base1), base2(base2){
}

void SnapshotField::save(){
    file = new FileWrite("saveField.txt", "save");
    std::ostringstream out;
    this->adapter = field->getAdapter();

    out << lenghtX << " " << lengthY << " " << maxCountObject  << std::endl;

    if (field->base1 == nullptr){
        out << "no" << std::endl;
        file->write(out.str());
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
        file->write(out.str());
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

    file->write(out.str());
    adapter->gameSaved();
}

void SnapshotField::load(Mediator* mediator){
    fileRead = new FileRead("saveField.txt");
    std::stringstream stream = fileRead->read();

    int fieldX, fieldY, maxCountUnit;
    adapter = new Adapter();

    try {
        stream >> fieldX;
        stream >> fieldY;
        stream >> maxCountUnit;
    }

    catch(int i) {
        std::cout << "Load file incorrect, loadding stopped" << std::endl;
        adapter->incorrectFile();
        return;
    }

    if (fieldX < 3 || fieldY < 3 || maxCountUnit <= 0){
        std::cout << "Load file incorrect, loadding stopped" << std::endl;
        adapter->incorrectFile();
        return;
    }

    Field*  newField = new Field(fieldX, fieldY, maxCountUnit, adapter);
    *(this->field) = *newField;
    field->addLandscape();
    mediator->setField(field);

    std::string flagContain;

    stream >> flagContain;

    if (flagContain != "yes" && flagContain != "no"){
        std::cout << "Load file incorrect, loadding stopped" << std::endl;
        adapter->incorrectFile();
        return;
    }

    if (flagContain == "no") {
        adapter->gameLoaded();
        return;
    }

    int baseX, baseY, maxCountUnitBase, health, countUnitBase, numberBase;

    try {
        stream >> baseX;
        stream >> baseY;
        stream >> maxCountUnitBase;
        stream >> health;
        stream >> countUnitBase;
        stream >> numberBase;
    }

    catch (int i){
        std::cout << "Load file incorrect, loadding stopped" << std::endl;
        adapter->incorrectFile();
        return;
    }

    if (baseX < 0 || baseY < 0 || maxCountUnitBase <= 0 || health < 0 || (numberBase != 1 && numberBase != 2)){
        std::cout << "Load file incorrect, loadding stopped" << std::endl;
        adapter->incorrectFile();
        return;
    }

    field->createBase(baseX, baseY, maxCountUnitBase, health, adapter);

    char name;
    int healthUnit, attack, armor, x, y;

    for (int i=0; i<countUnitBase; i++){
        try {
            stream >> name;
            stream >> healthUnit;
            stream >> attack;
            stream >> armor;
            stream >> x;
            stream >> y;
        }
        catch (int i){
            std::cout << "Load file incorrect, loadding stopped" << std::endl;
            adapter->incorrectFile();
            return;
        }

        if (healthUnit <= 0 || attack <= 0 || armor < 0 || x < 0 || y < 0){
            std::cout << "Load file incorrect, loadding stopped" << std::endl;
            adapter->incorrectFile();
            return;
        }

        field->base1->setUnit(name, x, y, healthUnit, attack, armor,  mediator, adapter);
    }

    stream >> flagContain;

    if (flagContain != "yes" && flagContain != "no"){
        std::cout << "Load file incorrect, loadding stopped" << std::endl;
        adapter->incorrectFile();
        return;
    }

    if (flagContain == "no") {
        adapter->gameLoaded();
        return;
    }

    try {
        stream >> baseX;
        stream >> baseY;
        stream >> maxCountUnitBase;
        stream >> health;
        stream >> countUnitBase;
        stream >> numberBase;
    }
    catch (int i){
        std::cout << "Load file incorrect, loadding stopped" << std::endl;
        adapter->incorrectFile();
        return;
    }

    if (baseX < 0 || baseY < 0 || maxCountUnitBase <= 0 || health < 0 || (numberBase != 1 && numberBase != 2)){
        std::cout << "Load file incorrect, loadding stopped" << std::endl;
        adapter->incorrectFile();
        return;
    }

    field->createBase(baseX, baseY, maxCountUnitBase, health, adapter);

    for (int i=0; i<countUnitBase; i++){
        try {
            stream >> name;
            stream >> healthUnit;
            stream >> attack;
            stream >> armor;
            stream >> x;
            stream >> y;
        }
        catch (int i){
            std::cout << "Load file incorrect, loadding stopped" << std::endl;
            adapter->incorrectFile();
            return;
        }

        if (healthUnit <= 0 || attack <= 0 || armor < 0 || x < 0 || y < 0){
            std::cout << "Load file incorrect, loadding stopped" << std::endl;
            adapter->incorrectFile();
            return;
        }

        field->base2->setUnit(name, x, y, healthUnit, attack, armor, mediator, adapter);
    }

    adapter->gameLoaded();
}


