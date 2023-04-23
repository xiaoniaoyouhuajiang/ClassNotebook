#include "UnitGroup.h"
#include "Landscape/ILandscape.h"


UnitGroup::UnitGroupSnapshot::UnitGroupSnapshot(UnitGroup& group) : objectType(group.getObjectType()), point(group.getPoint()), unitCount(group.unitSet.size()) {
    for (auto unit = group.unitSet.begin(); unit != group.unitSet.end(); unit++) {
        unitSnapVector.push_back(Unit::UnitSnapshot(**unit));
    }
    correct = true;
}

UnitGroup::UnitGroupSnapshot::UnitGroupSnapshot(std::ifstream& stream) : point(Point(0, 0)), unitCount(0) {
    correct = false;

    uint16_t objectType;
    if (!(stream >> objectType)) {
        return;
    }
    this->objectType = objectType;

    uint16_t x, y;
    if (!(stream >> x >> y)) {
        return;
    }
    point = Point(x, y);

    if (!(stream >> unitCount) || unitCount > MAX_GROUP_SIZE) {
        return;
    }


    for (auto i = 0; i < unitCount; i++) {
        std::string input;
        if (!(stream >> input)) {
            return;
        }

        if (input == "UNIT_START") {
            auto unitSnapshot = Unit::UnitSnapshot(stream);
            if (!unitSnapshot.isCorrect() || unitSnapshot.getObjectType() != objectType) {
                return;
            }
            unitSnapVector.push_back(unitSnapshot);
            if (!(stream >> input) || input != "UNIT_END") {
                return;
            }
        }
    }
    correct = true;
}

std::ofstream& operator<<(std::ofstream& stream, const UnitGroup::UnitGroupSnapshot& snapshot) {
    stream << snapshot.objectType << " ";
    stream << snapshot.point.getX() << " " << snapshot.point.getY() << " ";
    stream << snapshot.unitCount << std::endl;

    for (auto unitSnapshot = snapshot.unitSnapVector.begin(); unitSnapshot != snapshot.unitSnapVector.end(); unitSnapshot++) {
        stream << "UNIT_START" << std::endl;
        stream << *unitSnapshot;
        stream << "UNIT_END" << std::endl;
        if (unitSnapshot+1 != snapshot.unitSnapVector.end()) {
            stream << std::endl;
        }
    }

    return stream;
}
