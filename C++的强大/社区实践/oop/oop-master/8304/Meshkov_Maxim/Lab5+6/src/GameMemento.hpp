#pragma once

#include <vector>
#include <memory>

#include "FieldPosition.hpp"

class GameMemento {
public:
    int currentPlayer;
    int fieldWidth, fieldHeight;
    enum class TerrainType { GROUND, STONE, WATER };
    std::vector<TerrainType> terrains;
    struct BaseInfo {
        FieldPosition position;
        int player;
        int health;
        int creationAbility;
    };
    std::vector<BaseInfo> bases;
    enum class ThingType { MEDICINE, MICRO, POWERFUL, SMALL };
    struct ThingInfo {
        FieldPosition position;
        ThingType type;
    };
    std::vector<ThingInfo> things;
    enum class UnitType { DISTANCE_ARCHER, POWERFUL_ARCHER, HEAVY_KNIGHT, LIGHTWEIGHT_KNIGHT, FIRE_MAGE, ICE_MAGE};
    struct UnitInfo {
        FieldPosition position;
        UnitType type;
        int player;
        int health;
        bool isIced;
    };
    std::vector<UnitInfo> units;

public:
    void saveToFile(const std::string& filePathWithName) const;
    static std::shared_ptr<GameMemento> loadFromFile(const std::string& filePathWithName);
};
