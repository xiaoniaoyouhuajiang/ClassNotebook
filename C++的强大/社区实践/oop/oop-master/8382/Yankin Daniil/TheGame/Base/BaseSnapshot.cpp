#include "Base.h"
#include "Landscape/ILandscape.h"


Base::BaseSnapshot::BaseSnapshot(Base& base) : point(base.point), health(base.health), strength(base.strength), armor(base.armor) {
    correct = true;
}

Base::BaseSnapshot::BaseSnapshot(std::ifstream& stream) : point(Point(0, 0)) {
    correct = false;

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

    correct = true;
}

std::ofstream& operator<<(std::ofstream& stream, const Base::BaseSnapshot& snapshot) {
    stream << snapshot.point.getX() << " " << snapshot.point.getY() << " ";
    stream << snapshot.health.getMaxHealth() << " " << snapshot.health.getHealth() << " ";
    stream << snapshot.strength.getStrength() << " " << snapshot.strength.getRadius() << " ";
    stream << snapshot.armor.getArmor() << std::endl;
    return stream;
}
