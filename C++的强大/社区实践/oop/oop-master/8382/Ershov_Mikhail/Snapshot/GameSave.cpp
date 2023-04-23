#include "GameSave.h"

GameSave::GameSave(string name) : fileName(name) {
    file.open(name);
    if (!file.is_open())
        throw std::runtime_error("Файл не открывается!");
}


GameSave::~GameSave() {
    if (file.is_open())
        file.close();
}

void GameSave::save(SnapshotGame* snapshot) {
    if (!file.is_open()) {
        std::cout << "Сохранение игры невозможно, так как указан неверный файл\n";
        return;
    }

    file << "Field:\n";
    file << snapshot->getSize() << " " << snapshot->getField()->getWhoseTurn() << "\n";
    file << "Units:\n";

    for (unsigned i = 0; i < snapshot->getSize(); i++) {
        for (unsigned j = 0; j < snapshot->getSize(); j++) {
            file << snapshot->getField()->getCell()[i][j].getUnit().GetValue() << " ";
            file << snapshot->getField()->getCell()[i][j].getUnit().GetHealth() << " ";
            file << snapshot->getField()->getCell()[i][j].getUnit().GetArmor() << " ";
            file << snapshot->getField()->getCell()[i][j].getUnit().GetDamage() << "\n";
        }
        file << "\n";
    }

    file << "Landscape:\n";
    for (unsigned i = 0; i < snapshot->getSize(); i++) {
        for (unsigned j = 0; j < snapshot->getSize(); j++) {
            if (snapshot->getField()->getCell()[i][j].getLandscape() != nullptr) file << snapshot->getField()->getCell()[i][j].getLandscape()->getLandscapeType() << " ";
        }
        file << "\n";
    }

    file << "NeutObjects:\n";
    for (unsigned i = 0; i < snapshot->getSize(); i++) {
        for (unsigned j = 0; j < snapshot->getSize(); j++) {
            if (snapshot->getField()->getCell()[i][j].getNeutral() == nullptr) file << "0 ";
            else file << snapshot->getField()->getCell()[i][j].getNeutral()->getNeutObjType() << " ";
        }
        file << "\n";
    }

    file << "Bases:\n";
    file << snapshot->getBases().size() << "\n";
    for (SnapshotBase* base : snapshot->getBases()) {
        file << base->getTypeOfBase() << " " << base->getHealth() << " " <<
            base->getCurrentOrcsNum() << " " << base->getCurrentMENum() << "\n";
        file << base->getUnits().size() << "\n";
        for (SnapshotUnit* unit : base->getUnits()) {
            file << unit->getName() << " ";
            file << unit->getHealth() << " " << unit->getArmor() << " " << unit->getDamage() << " " << unit->getX() << " " << unit->getY() << " " << "\n";
        }
    }
}