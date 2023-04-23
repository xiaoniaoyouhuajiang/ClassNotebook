#include "GameMemento.hpp"

#include <fstream>

void GameMemento::saveToFile(const std::string& filePathWithName) const {
    std::ofstream fout(filePathWithName);
    if (!fout.is_open())
        throw FileError("saveToFile: file opening failure.");

    fout << currentPlayer << " " << fieldWidth << " " << fieldHeight << std::endl;

    for (auto terrain : terrains) {
        fout << (int)terrain << " ";
    }
    fout << std::endl;
    fout << bases.size() << " ";
    for (auto baseInfo : bases) {
        fout << baseInfo.position.row << " " << baseInfo.position.col << " ";
        fout << baseInfo.player << " " << baseInfo.health << " " << baseInfo.creationAbility << " ";
    }
    fout << std::endl;
    fout << things.size() << " ";
    for (auto thingInfo : things) {
        fout << thingInfo.position.row << " " << thingInfo.position.col << " ";
        fout << (int)thingInfo.type << " ";
    }
    fout << std::endl;
    fout << units.size() << " ";
    for (auto unitInfo : units) {
        fout << unitInfo.position.row << " " << unitInfo.position.col << " ";
        fout << (int)unitInfo.type << " " << unitInfo.player << " " << unitInfo.health << " " << unitInfo.isIced << " ";
    }
    fout << std::endl;
}

std::shared_ptr<GameMemento> GameMemento::loadFromFile(const std::string& filePathWithName) {
    auto memento = std::make_shared<GameMemento>();

    std::ifstream fin(filePathWithName);
    if (!fin.is_open())
        throw FileError("loadFromFile: file opening failure.");

    auto goodPosition = fin.tellg();
    fin.exceptions (std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
    try {
        fin >> memento->currentPlayer >> memento->fieldWidth >> memento->fieldHeight;

        for (int i = 0; i < memento->fieldWidth * memento->fieldHeight; i++) {
            goodPosition = fin.tellg();
            int terrainId;
            fin >> terrainId;
            memento->terrains.push_back((GameMemento::TerrainType)terrainId);
        }
        goodPosition = fin.tellg();
        int basesNumber;
        fin >> basesNumber;
        for (int i = 0; i < basesNumber; i++) {
            goodPosition = fin.tellg();
            BaseInfo baseInfo;
            fin >> baseInfo.position.row >> baseInfo.position.col;
            fin >> baseInfo.player >> baseInfo.health >> baseInfo.creationAbility;
            memento->bases.push_back(baseInfo);
        }
        goodPosition = fin.tellg();
        int thingsNumber;
        fin >> thingsNumber;
        for (int i = 0; i < thingsNumber; i++) {
            goodPosition = fin.tellg();
            ThingInfo thingInfo;
            fin >> thingInfo.position.row >> thingInfo.position.col;
            int thingTypeId;
            fin >> thingTypeId;
            thingInfo.type = (ThingType)thingTypeId;
            memento->things.push_back(thingInfo);
        }
        goodPosition = fin.tellg();
        int unitsNumber;
        fin >> unitsNumber;
        for (int i = 0; i < unitsNumber; i++) {
            goodPosition = fin.tellg();
            UnitInfo unitInfo;
            fin >> unitInfo.position.row >> unitInfo.position.col;
            int unitTypeId;
            fin >> unitTypeId >> unitInfo.player >> unitInfo.health >> unitInfo.isIced;
            unitInfo.type = (UnitType)unitTypeId;
            memento->units.push_back(unitInfo);
        }
        return memento;
    }
    catch (const std::ifstream::failure &e) {
        fin.exceptions(std::istream::goodbit);
        throw FileError("loadFromFile: bad save file (last known good position is " + std::to_string(goodPosition) + ")");
    }
}
