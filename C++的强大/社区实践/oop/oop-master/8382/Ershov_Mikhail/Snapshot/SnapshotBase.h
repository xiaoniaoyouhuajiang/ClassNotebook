#pragma once

#include "SnapshotUnit.h"
#include <vector>

class SnapshotBase {
public:
    SnapshotBase(char type, int hp, int numOfOrcs, int numOfME, vector<SnapshotUnit*> units);
    char getTypeOfBase() const;
    int getHealth() const;
    int getCurrentOrcsNum() const;
    int getCurrentMENum();
    vector<SnapshotUnit*> getUnits() const;

private:
    char typeOfBase;
    int health;
    int currentOrcsNum;
    int currentMEnum;
    vector<SnapshotUnit*> units;
};
