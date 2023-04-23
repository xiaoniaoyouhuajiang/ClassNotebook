#include "SnapshotUnit.h"

SnapshotUnit::SnapshotUnit(string name, int damage, int health, int armor, unsigned x, unsigned y) : name(name), damage(damage),
health(health), armor(armor), x(x), y(y) {

}

string SnapshotUnit::getName() const {
    return name;
}

int SnapshotUnit::getArmor() const {
    return armor;
}

int SnapshotUnit::getHealth() const {
    return health;
}

int SnapshotUnit::getDamage() const {
    return damage;
}

unsigned SnapshotUnit::getX() const {
    return x;
}

unsigned SnapshotUnit::getY() const {
    return y;
}
