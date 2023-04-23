#include "SnapshotBase.h"

SnapshotBase::SnapshotBase(char type, int hp, int numOfOrcs, int numOfME, vector<SnapshotUnit*> units) :
    typeOfBase(type), health(hp), currentOrcsNum(numOfOrcs), currentMEnum(numOfME), units(units) {

}

char SnapshotBase::getTypeOfBase() const {
    return typeOfBase;
}

int SnapshotBase::getHealth() const {
    return health;
}

int SnapshotBase::getCurrentOrcsNum() const {
    return currentOrcsNum;
}

int SnapshotBase::getCurrentMENum() {
    return currentMEnum;
}

vector<SnapshotUnit*> SnapshotBase::getUnits() const {
    return units;
}