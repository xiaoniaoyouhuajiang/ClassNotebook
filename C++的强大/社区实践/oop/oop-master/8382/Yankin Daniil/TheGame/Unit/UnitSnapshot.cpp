#include "Unit.h"
#include "Landscape/ILandscape.h"


Unit::UnitSnapshot::UnitSnapshot(Unit& unit) : objectType(unit.getObjectType()), point(unit.point), health(unit.health), strength(unit.strength),
    armor(unit.armor), movePoints(unit.movePoints), attacked(unit.attacked) {
    correct = true;
}

Unit::UnitSnapshot::UnitSnapshot(std::ifstream& stream) : point(Point(0, 0)) {
    correct = false;

    if (!(stream >> objectType) || objectType < UNIT_SWORDSMAN || objectType > UNIT_RAM) {
        return;
    }

    uint16_t x, y;
    if (!(stream >> x >> y)) {
        return;
    }
    point = Point(x, y);

    uint16_t maxHealthValue, healthValue;
    if (!(stream >> maxHealthValue >> healthValue)) {
        return;
    }
    if (maxHealthValue == 0 || healthValue == 0) {
        return;
    }
    health = Health(maxHealthValue, healthValue);

    uint16_t strengthValue;
    uint16_t radiusValue;
    if (!(stream >> strengthValue >> radiusValue)) {
        return;
    }
    strength = Strength(strengthValue, radiusValue);

    uint16_t armorValue;
    if (!(stream >> armorValue)) {
        return;
    }
    armor = Armor(armorValue);

    uint16_t maxMovePointsValue, movePointsValue;
    if (!(stream >> maxMovePointsValue >> movePointsValue)) {
        return;
    }
    movePoints = MovePoints(maxMovePointsValue, movePointsValue);

    if (!(stream >> attacked)) {
        return;
    }

    correct = true;
}

std::ofstream& operator<<(std::ofstream& stream, const Unit::UnitSnapshot& snapshot) {
    stream << snapshot.objectType << " ";
    stream << snapshot.point.getX() << " " << snapshot.point.getY() << " ";
    stream << snapshot.health.getMaxHealth() << " " << snapshot.health.getHealth() << " ";
    stream << snapshot.strength.getStrength() << " " << snapshot.strength.getRadius() << " ";
    stream << snapshot.armor.getArmor() << " ";
    stream << snapshot.movePoints.getMaxMovePoints() << " " << snapshot.movePoints.getMovePoints() << " ";
    stream << snapshot.attacked << std::endl;
    return stream;
}

uint16_t Unit::UnitSnapshot::getObjectType() const {
    return objectType;
}
